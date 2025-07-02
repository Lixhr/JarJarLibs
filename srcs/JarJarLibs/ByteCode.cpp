#include "ByteCode.hpp"

int getInt(const uint8_t *begin) {
    return (
            begin[0] << 24 
        |   begin[1] << 16
        |   begin[2] << 8
        |   begin[3] 
    );
}

ByteCode::~ByteCode() {}
size_t ByteCode::getOpcodeLen(const uint8_t *current, size_t i) {
    uint8_t opcode = current[0];

    if (opcode > 0xc9) {
        return (1);
    }

    // https://docs.oracle.com/javase/specs/jvms/se11/html/jvms-6.html#jvms-6.5.wide
    if (opcode == 0xc4) { // 
        uint8_t arg = current[1];

        if ((arg >= 0x15 && arg <= 0x19) || (arg >= 0x36 && arg <= 0x3a) || arg == 0xa9) {
            return (4);
        }
        return (6);
    }

    if (opcode == 0xab) { // lookupswitch
        size_t pad = 0;
        while ((i + 1 + pad) % 4 != 0) {
            pad++;
        }
        int npairs = getInt(&(current[1 + pad + 4]));
        return 1 + pad + 8 + (npairs * 8);
    }
    
    // https://docs.oracle.com/javase/specs/jvms/se11/html/jvms-6.html#jvms-6.5.tableswitch
    if (opcode == 0xaa) { // tableswitch
        size_t pad = 0;
        while ((i + 1 + pad) % 4 != 0) {
            pad++;
        }
        int low = getInt(&(current[1 + pad + 4]));
        int high = getInt(&(current[1 + pad + 8]));
        return 1 + pad + 12 + 4 * (high - low + 1);
    }

    return (opcode_length[opcode]);
}

std::string getCalledClass(ares::ConstantInfo &cp_info, ares::ClassFile &class_file) {
    uint16_t class_index = cp_info.field_method_info.class_index;

    const auto &class_cp = class_file.constant_pool[class_index - 1];
    ares::ConstantPoolInfo& called_class = class_file.constant_pool[class_cp.info.class_info.name_index - 1];

    std::string class_name(reinterpret_cast<const char *>(called_class.info.utf8_info.bytes), called_class.info.utf8_info.length);

    return (class_name);
}

std::string getCalledMethod(ares::ConstantInfo &cp_info, ares::ClassFile &class_file) {
    uint16_t name_and_type_index = cp_info.field_method_info.name_and_type_index;

    ares::ConstantPoolInfo& name_and_type_entry = class_file.constant_pool[name_and_type_index - 1];
    uint16_t method_name_index = name_and_type_entry.info.name_and_type_info.name_index;

    const auto &name_cp = class_file.constant_pool[method_name_index - 1];
    std::string method_name(reinterpret_cast<const char *>(name_cp.info.utf8_info.bytes), name_cp.info.utf8_info.length);

    return (method_name);
}

bool    isMethodInteresting(std::string &class_name) {
    if (class_name.find("java") != std::string::npos) {
        return (false);
    }
    return (true);
}

void ByteCode::findFunctionCalls(const ares::MethodInfo &method, ares::ClassFile &class_file) {
    for (const auto &attribute : method.attributes) {
        const ares::ConstantPoolInfo &attr_name_cp = class_file.constant_pool[attribute.attribute_name_index - 1];
        std::string attr_name(reinterpret_cast<const char *>(attr_name_cp.info.utf8_info.bytes), attr_name_cp.info.utf8_info.length);
        if (attr_name == "Code") {
            size_t i = 0;
            const uint8_t *ptr = attribute.info;

            uint32_t code_length = getInt(&ptr[4]);
            ptr += 8;
            while (i < code_length) {
                uint8_t opcode = ptr[i];
                size_t len = getOpcodeLen(&(ptr[i]), i);

                if (opcode >= INVOKEVIRTUAL && opcode <= INVOKEDYNAMIC) {
                    uint16_t index = (ptr[i + 1] << 8) | ptr[i + 2];
                    ares::ConstantPoolInfo& const_pool = class_file.constant_pool[index - 1];
                    if (const_pool.tag == ares::ConstantPoolInfo::METHOD_REF) {
                        ares::ConstantInfo &cp_info = const_pool.info;

                        std::string called_class = getCalledClass(cp_info, class_file);
                        std::replace(called_class.begin(), called_class.end(), '/', '.');

                        if (isMethodInteresting(called_class)) {
                            called_class += "." + getCalledMethod(cp_info, class_file);
                            class_file.pushFunctionCall(called_class);
                        }
                    }
                }
                i += len;
            }
        }
    }
}
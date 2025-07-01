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

    // https://docs.oracle.com/javase/specs/jvms/se11/html/jvms-6.html#jvms-6.5.lookupswitch
    if (opcode == 0xab) { // lookupswitch
        size_t pad = 1;
        while ((pad + i) % 4 != 0) pad ++;

        int npairs = getInt(&(current[pad + 4]));

        return (pad + 8 + (npairs * 8));
    }

    if (opcode == 0xaa) {
        size_t pad = 1;
        while ((pad + i) % 4 != 0) pad ++;

        int low = getInt(&(current[pad + 4]));
        int high = getInt(&(current[pad + 8]));

        return (pad + 12 + 4 * (high - low + 1));
    }

    return (opcode_length[opcode]);
}

void ByteCode::findFunctionCalls(const ares::MethodInfo &method, ares::ClassFile &class_file) {
    for (const auto &attribute : method.attributes) {
        const auto &attr_name_cp = class_file.constant_pool[attribute.attribute_name_index - 1];
        std::string attr_name(reinterpret_cast<const char *>(attr_name_cp.info.utf8_info.bytes), attr_name_cp.info.utf8_info.length);
        if (attr_name == "Code") {
            size_t i = 0;
            const uint8_t *ptr = attribute.info;

            uint32_t code_length = getInt(&ptr[4]);
            ptr += 8;
            while (i < code_length) {
                uint8_t opcode = ptr[i];
                size_t len = getOpcodeLen(&(ptr[i]), i);

                printf("=============================OP : %x\n", opcode);

                if (opcode >= 0xb6 && opcode <= 0xba) {
                    uint16_t index = ptr[i + 1] << 8 | ptr[i + 2];
                    // const auto cp = class_file.constant_pool[index -1];
                    std::cout << "TODO!!" << std::endl;
                    // std::cout << cp.info.utf8_info.bytes ;
                    printf("INVOKE %d\n", index);
                }
                i += len;
            }
        }
    }
}
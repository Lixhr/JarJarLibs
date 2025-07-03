#include "ProcessedMethod.hpp"

ProcessedMethod::ProcessedMethod(const ares::MethodInfo &method, const std::vector<ares::ConstantPoolInfo>& cp) :  is_native(false) {
    const auto &cp_item = cp[method.name_index - 1];

    std::string method_name(reinterpret_cast<const char *>(cp_item.info.utf8_info.bytes), cp_item.info.utf8_info.length);
    this->name = method_name;

    if ((method.access_flags & ares::MethodInfo::AccessFlag::NATIVE) != 0) {
        is_native = true;
    }
}

ProcessedMethod::~ProcessedMethod() {
}

void ProcessedMethod::pushFunctionCall(std::string &class_, std::string name) {
    t_func_call new_func = {name, class_};

    called_functions.insert(new_func);
}
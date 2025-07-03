#pragma once
#include "constant_info.h"
#include "method_info.h"
#include <iostream>
#include <set>

typedef struct func {
    std::string name;
    std::string class_name;

    bool operator<(const func &other) const {
        return std::tie(class_name, name) < std::tie(other.class_name, other.name);
    }
}   t_func_call;

class ProcessedMethod
{
    private:
    public:
        bool    is_native;
        std::string name;
        ProcessedMethod(const ares::MethodInfo &method, const std::vector<ares::ConstantPoolInfo>& cp);
        ~ProcessedMethod();
        void pushFunctionCall(std::string &class_, std::string name);
        std::set<t_func_call> called_functions;
};
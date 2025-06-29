#pragma once
#include "jjl.hpp"
#include "class_file.h"
#include "method_info.h"

class JniOwner
{
    private:
        const ares::ClassFile &jni_class;
        std::vector <const ares::MethodInfo *> jni_methods;
    public:
        JniOwner(const ares::ClassFile &jni_class, std::vector <const ares::MethodInfo *> jni_methods);
        ~JniOwner();
};

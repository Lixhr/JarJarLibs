#pragma once
#include "ares.h"
#include <iostream>
#include "jvm_opcodes.h"
#include <algorithm>
#include <cstring>

class ByteCode
{
    private:
        ByteCode();
        ~ByteCode();
        static size_t getOpcodeLen(const uint8_t *current, size_t i);

    public:
        static void findFunctionCalls(const ares::MethodInfo &method, ares::ClassFile &classfile);
};
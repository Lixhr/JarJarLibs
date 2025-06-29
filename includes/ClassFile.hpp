#pragma once
#include "jjl.hpp"

#define CLASS_MAGIC 0xCAFEBABE

class ClassFile
{
    private:
        filesystem::path file_name;
        void readFile();
        std::vector <ares::ConstantPoolInfo> constant_pool{};
    public:
        ClassFile(filesystem::path file_name);
        ~ClassFile();
};

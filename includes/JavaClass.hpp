#pragma once
#include "jjl.hpp"

class JavaClass
{
    private:
        const string className;
        const string &jarFile;
        void setClassData();
    public:
        JavaClass(string &className, const string &jar_file);
        ~JavaClass();
};

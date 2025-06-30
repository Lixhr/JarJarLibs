#pragma once
#include "jjl.hpp"
#include "JavaClass.hpp"

class JarJarLibs
{
    private:
        const string &file;
        void getJavaClass(void);
        std::vector<JavaClass> classes;
    public:
        JarJarLibs(const string &file);
        ~JarJarLibs();
};
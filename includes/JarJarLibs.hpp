#pragma once
#include "jjl.hpp"
#include "JniOwner.hpp"

class JarJarLibs
{
    private:
        vector<JarFile> jar_files;
    public:
        JarJarLibs(const string &file);
        ~JarJarLibs();
};
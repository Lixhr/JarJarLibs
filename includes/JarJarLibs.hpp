#pragma once
#include "jjl.hpp"
#include "ares.h"
#include <map>
#include <algorithm>

class JarJarLibs
{
    private:
        const string &file;
        std::vector<ares::JARFile> jars;
        std::map<std::string, std::shared_ptr<ares::ClassFile>> classes;
    public:
        JarJarLibs(const string &file);
        ~JarJarLibs();
};

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
        void processNativeMethods();
        void findFunctionCaller(const std::string &class_name, const std::string &func, size_t depth, 
            std::set<std::pair<std::string, std::string>> &visited);
    public:
        JarJarLibs(const string &file);
        ~JarJarLibs();
};

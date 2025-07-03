#pragma once
#include "jjl.hpp"
#include "ares.h"
#include <map>
#include <algorithm>
#include "GraphViz.hpp"

#define MAX_DEPTH 50

class JarJarLibs
{
    private:
        const string &file;
        std::vector<ares::JARFile> jars;
        void processNativeMethods();
        void findFunctionCaller(const std::string &class_name, const std::string &func, size_t depth, 
            std::set<std::pair<std::string, std::string>> &visited);
        GraphViz dot;
    public:
        JarJarLibs(const string &file);
        ~JarJarLibs();
};

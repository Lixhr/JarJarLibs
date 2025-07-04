#pragma once
#include "jjl.hpp"
#include "ares.h"
#include <map>
#include <algorithm>
#include "GraphViz.hpp"
#include "ArgsParser.hpp"

#define MAX_DEPTH 50


class JarJarLibs
{
    private:
        std::vector<ares::JARFile> jars;
        void processNativeMethods();
        void processRecursiveDirectories();
        bool shouldBeProcessed(const std::string &class_name, const std::string &method_name, bool default_);
        void findFunctionCaller(const std::string &class_name, const std::string &func, size_t depth, 
            std::set<std::pair<std::string, std::string>> &visited);
        GraphViz dot;
        const ArgsParser &args;
    public:
        JarJarLibs(const ArgsParser &args);
        ~JarJarLibs();
};

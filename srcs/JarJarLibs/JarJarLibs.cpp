#include "JarJarLibs.hpp"
#include "ares.h"
#include <filesystem>
#include <set>
#include <utility>
#include "GraphViz.hpp"

void JarJarLibs::processRecursiveDirectories() {
    using recursive_directory_iterator = std::filesystem::recursive_directory_iterator;
    for (const auto& jarfile : recursive_directory_iterator(args.input)) {
        try {
            this->jars.push_back(ares::JARFile::read_file(jarfile.path()));
            ares::JARFile &jar = this->jars.back();
            for (auto &class_pair : jar.classes) {
                auto &class_file = class_pair.second;
                class_file.setTreeData();
            }
        }
        catch (const std::exception &e) {
            std::cerr << e.what() << std::endl;
        }
    }
}

JarJarLibs::JarJarLibs(const ArgsParser &args) : args(args) {
    if (args.is_recursive) {
        this->processRecursiveDirectories();
    }
    else {
        this->jars.push_back(ares::JARFile::read_file(args.input));
        ares::JARFile &jar = this->jars.back();
        for (auto &class_pair : jar.classes) {
            auto &class_file = class_pair.second;
            class_file.setTreeData();
        }
    }

    this->processNativeMethods();
    this->dot.test();
}

bool JarJarLibs::shouldBeProcessed(const std::string &class_name, const std::string &method_name, bool default_) {
    if (args.include_regex.isEnabled()) {
        return args.include_regex.matches(class_name, method_name);
    }
    
    bool should_process = default_;
    
    if (should_process && args.exclude_regex.isEnabled()) {
        return (!args.exclude_regex.matches(class_name, method_name));
    }
    
    return should_process;
}

void JarJarLibs::findFunctionCaller(const std::string &class_name, const std::string &func, size_t depth,
                                    std::set<std::pair<std::string, std::string>> &visited) {
    if (depth == 0) return;

    auto current = std::make_pair(class_name, func);
    if (visited.count(current) != 0) return;
    visited.insert(current);

    for (auto &jar : this->jars) {
        for (auto &class_pair : jar.classes) {
            for (auto &method : class_pair.second.processed_methods) {
                if (method.name == func && class_pair.first == class_name) {
                    continue;
                }
                for (auto &called_func : method.called_functions) {
                    if (called_func.name == func && called_func.class_name == class_name ){
                        if (shouldBeProcessed(class_pair.first, method.name, true)) {
                            this->dot.addRelation({
                                    called_func.class_name,
                                    called_func.name,
                                    class_pair.first,
                                    method.name,
                                    depth == (size_t)args.recursion_depth
                            });
                            findFunctionCaller(class_pair.first, method.name, depth - 1, visited);
                        }
                    }
                }
            }
        }
    }
}

void JarJarLibs::processNativeMethods() {
    std::set<std::pair<std::string, std::string>> visited;

    for (auto &jar : this->jars) {
        for (auto &class_pair : jar.classes) {
            for (auto &method : class_pair.second.processed_methods) {
                if ((args.is_jni && method.is_native) || args.include_regex.isEnabled()) {
                    if (shouldBeProcessed(class_pair.first, method.name, true))
                        findFunctionCaller(class_pair.first, method.name, args.recursion_depth, visited);
                }
            }
        }
    }
}



JarJarLibs::~JarJarLibs() {
}

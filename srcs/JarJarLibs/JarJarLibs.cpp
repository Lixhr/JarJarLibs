#include "JarJarLibs.hpp"
#include "ares.h"
#include <filesystem>
#include <set>
#include <utility>
#include "GraphViz.hpp"

JarJarLibs::JarJarLibs(const string &starting_path) : file(starting_path) {
    using recursive_directory_iterator = std::filesystem::recursive_directory_iterator;

    for (const auto& jarfile : recursive_directory_iterator(starting_path)) {
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
    this->processNativeMethods();

    this->dot.test();
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
                    if (called_func.name == func && called_func.class_name == class_name) {
                        this->dot.addRelation({
                                called_func.class_name,
                                called_func.name,
                                class_pair.first,
                                method.name,
                                depth == MAX_DEPTH
                        });
                        findFunctionCaller(class_pair.first, method.name, depth - 1, visited);
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
                if (method.is_native) {
                    findFunctionCaller(class_pair.first, method.name, MAX_DEPTH, visited);
                }
            }
        }
    }
}



JarJarLibs::~JarJarLibs() {
}

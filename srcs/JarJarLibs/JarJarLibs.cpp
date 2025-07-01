#include "JarJarLibs.hpp"
#include "ares.h"

JarJarLibs::JarJarLibs(const string &file) : file(file) {
    this->jars.push_back(ares::JARFile::read_file(file));

    for (auto &jar : this->jars) {
        for (auto &class_pair : jar.classes) {
            const auto &class_name = class_pair.first;
            auto &class_file = class_pair.second;

            std::cout << "===============CLASS: " << class_name << std::endl;
            class_file.setTreeData();
            // classes[class_name] = std::make_shared<ares::ClassFile>(class_file);
        }
    }
}


JarJarLibs::~JarJarLibs() {
}

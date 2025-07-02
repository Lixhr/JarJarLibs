#include "JarJarLibs.hpp"
#include "ares.h"

JarJarLibs::JarJarLibs(const string &file) : file(file) {
    this->jars.push_back(ares::JARFile::read_file(file));

    for (auto &jar : this->jars) {
        for (auto &class_pair : jar.classes) {
            std::string class_name = class_pair.first;
            auto &class_file = class_pair.second;

            class_name.erase(class_name.end() - 6,  class_name.end());
            std::replace(class_name.begin(), class_name.end(), '/', '.'); // normalize

            class_file.setTreeData();
            classes[class_name] = std::make_shared<ares::ClassFile>(class_file);
        }
    }
}

JarJarLibs::~JarJarLibs() {
}

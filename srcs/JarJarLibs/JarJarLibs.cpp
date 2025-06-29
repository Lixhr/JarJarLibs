#include "JarJarLibs.hpp"
#include "JarFile.hpp"

JarJarLibs::JarJarLibs(const string &file) {
    this->jar_files.push_back(JarFile(file));
}

JarJarLibs::~JarJarLibs() {
}

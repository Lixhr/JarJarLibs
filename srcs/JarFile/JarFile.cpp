#include "JarFile.hpp"

filesystem::path JarFile::unJar(const string file_name) {
    try {
        checkFileFormat(file_name);
        const filesystem::path dest = createFolder(file_name);
        doUnzip(dest, file_name);
        return (dest);
    }
    catch (...) {
        throw;
    }
}

void    JarFile::getClassFiles() {
    try {
        for (const auto& entry : filesystem::recursive_directory_iterator(this->extr_folder)) {
            if (filesystem::is_regular_file(entry.path())) {
                try {
                    if (get_file_signature(entry.path()) == 0xCAFEBABE) {   
                        this->classes.push_back(ares::ClassFile(entry.path()));
                    }
                }
                catch (const std::exception &e) {
                    cerr << "Error : " << e.what() << std::endl;
                }
            }
        }
    } 
    catch (const std::exception& e) {
        cerr << "Error: " << e.what() << '\n';
    }
}

void    JarFile::fetchJNIOwners(void) {
    for (auto it = this->classes.begin(); it != this->classes.end(); it ++) {
        const ares::ClassFile &jni_class = *it;
        std::vector <const ares::MethodInfo *> jni_methods = it->getJNIMethods();
        if (!jni_methods.empty()) {
            this->jni_owners.push_back(new JniOwner(jni_class, jni_methods));
        }
    }
}

const vector<const JniOwner *> &JarFile::getJNIOwners() {
    return (this->jni_owners);
}


JarFile::JarFile(const string jar_name) {
    this->extr_folder = this->unJar(jar_name);
    this->getClassFiles();
    this->fetchJNIOwners();

}

JarFile::~JarFile() {
    for (auto it = this->jni_owners.begin(); it != this->jni_owners.end(); it ++) {
        delete *it;
    }
}

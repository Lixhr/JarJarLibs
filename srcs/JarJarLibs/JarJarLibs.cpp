#include "JarJarLibs.hpp"
#include "GNL.hpp"

JarJarLibs::JarJarLibs(const string &file) : file(file) {
    this->getJavaClass();
}

JarJarLibs::~JarJarLibs() {
}

void JarJarLibs::getJavaClass(void) {
    int fd = do_sys_command_stream("jar tf " + this->file);

    GNL reader(fd);

    char *c_line = NULL; 

    while ((c_line = reader.get_next_line()) != NULL) {
        std::string line(c_line);
        size_t extension;
        if ((extension = line.find(".class")) != string::npos) {
            line.erase(extension);
            size_t path;
            while ((path = line.find("/")) != string::npos) {
                line.replace(path, 1, ".");
            }
            std::cout << line <<endl;
            this->classes.push_back(JavaClass(line, this->file));
        }
        free(c_line);
    }
}
#include "jjl.hpp"

int open_file(const string &file_name) {
    int fd = open(file_name.c_str(), O_RDONLY);

    if (fd == -1) {
        throw (runtime_error("Unable to open file " + file_name));
    }
    return (fd);
}
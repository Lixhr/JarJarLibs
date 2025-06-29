#include "jjl.hpp"

uint32_t    get_file_signature(const string &file_name) {
    int fd = open_file(file_name);

    uint32_t file_header;
    read(fd, &file_header, sizeof(file_header));

    if (isLittleEndian()) {
        file_header = byte_swap(file_header);
    }

    close(fd);
    return (file_header);
}
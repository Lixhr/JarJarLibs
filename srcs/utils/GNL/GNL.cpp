#include "GNL.hpp"
#include <fcntl.h>

GNL::GNL(int fd) : fd(fd) {
    *buffer = 0;
}

void GNL::skip_next_line() {
    void *p = this->get_next_line();
    free(p);
}

GNL::~GNL() {
    close(fd);
}

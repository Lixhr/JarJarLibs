#pragma once
#include "get_next_line.h"
#include "jjl.hpp"

class GNL {
    private:
        char	buffer[BUFFER_SIZE + 1];
        int     fd;
    public:
        GNL(int fd);
        ~GNL();
        char	*get_next_line();
        void    skip_next_line();
};

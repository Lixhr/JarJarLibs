#include "jjl.hpp"

string get_args(int argc, char **argv) {
    if (argc < 2) {
        throw (invalid_argument("Invalid arg."));
    }
    return (argv[1]);
}
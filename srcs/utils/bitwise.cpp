#include "jjl.hpp"

bool isLittleEndian() {
    static unsigned long x = 1;
    static bool result(reinterpret_cast<unsigned char*>(&x)[0] != 0);
    return result;
}
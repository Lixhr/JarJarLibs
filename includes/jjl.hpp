#pragma once
#include <stdexcept>
#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <vector>
#include <sstream>
#include <filesystem>
#include "unistd.h"
#include <sys/wait.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <bit>

#include "ares/attribute_info.h"
#include "ares/class_file.h"
#include "ares/class_reader.h"
#include "ares/class_writer.h"
#include "ares/constant_info.h"
#include "ares/field_info.h"
#include "ares/method_info.h"
#include "ares/vm_check.h"


# define sqbrackets(txt) "[" + txt + "]"

# define TMP_DIR "./tmp/"

using namespace std;

class JarFile;

string              get_args(int, char **);
int                 open_file(const string &file_name);


uint32_t            get_file_signature(const string &file_name);
bool                isLittleEndian();
// uint 16 32 64
template<typename T>
T byte_swap(T data) {
    T ret = 0;
    uint8_t *pData = reinterpret_cast<uint8_t*>(&data);
    uint8_t *pRet = reinterpret_cast<uint8_t*>(&ret);
    size_t bytes = sizeof(T);

    for (size_t i = 0; i < bytes; i++) {
        pRet[i] = pData[bytes - 1 - i];
    }
    return (ret);
}
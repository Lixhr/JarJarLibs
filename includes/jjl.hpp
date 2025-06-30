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

# define sqbrackets(txt) "[" + txt + "]"

# define TMP_DIR "./tmp/"

using namespace std;

string              get_args(int, char **);
int do_sys_command_stream(const std::string &cmd);
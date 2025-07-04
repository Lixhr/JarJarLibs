#include <iostream>
#include <stdexcept>
#include <string>
#include <regex>
#include "ArgsParser.hpp"

void print_help() {
    std::cout << R"(
        ▄▄▄██▀▀▀▄▄▄       ██▀███  ▄▄▄██▀▀▀▄▄▄       ██▀███   ██▓     ██▓ ▄▄▄▄     ██████ 
        ▒██  ▒████▄    ▓██ ▒ ██▒  ▒██  ▒████▄    ▓██ ▒ ██▒▓██▒    ▓██▒▓█████▄ ▒██    ▒ 
        ░██  ▒██  ▀█▄  ▓██ ░▄█ ▒  ░██  ▒██  ▀█▄  ▓██ ░▄█ ▒▒██░    ▒██▒▒██▒ ▄██░ ▓██▄   
    ▓██▄██▓ ░██▄▄▄▄██ ▒██▀▀█▄ ▓██▄██▓ ░██▄▄▄▄██ ▒██▀▀█▄  ▒██░    ░██░▒██░█▀    ▒   ██▒
    ▓███▒   ▓█   ▓██▒░██▓ ▒██▒▓███▒   ▓█   ▓██▒░██▓ ▒██▒░██████▒░██░░▓█  ▀█▓▒██████▒▒
    ▒▓▒▒░   ▒▒   ▓▒█░░ ▒▓ ░▒▓░▒▓▒▒░   ▒▒   ▓▒█░░ ▒▓ ░▒▓░░ ▒░▓  ░░▓  ░▒▓███▀▒▒ ▒▓▒ ▒ ░
    ▒ ░▒░    ▒   ▒▒ ░  ░▒ ░ ▒░▒ ░▒░    ▒   ▒▒ ░  ░▒ ░ ▒░░ ░ ▒  ░ ▒ ░▒░▒   ░ ░ ░▒  ░ ░
    ░ ░ ░    ░   ▒     ░░   ░ ░ ░ ░    ░   ▒     ░░   ░   ░ ░    ▒ ░ ░    ░ ░  ░  ░  
    ░   ░        ░  ░   ░     ░   ░        ░  ░   ░         ░  ░ ░   ░            ░  
                                                                            ░          
    Usage: ./jjl [options] input
    Options:
        -h, --help              show this help message
        -r, --recursive         recursively process all .jar files in the input directory
        -x, --exclude <regex>   exclude matching patterns (e.g. "lib|render|test|sql")
        -i, --include <regex>   include only matching patterns (e.g. "system|native")
        -j, --jni               start traversal from JNI methods
        -d, --depth <value>     maximum depth of function call recursion
        -o, --output <file>     output .dot file
    )" << std::endl;
}

std::string get_next_arg(int& i, int argc, char* argv[], const std::string& flag) {
    if (i + 1 >= argc)
        throw std::invalid_argument(flag + ": expected value after flag");
    return argv[++i];
}

ArgsParser::ArgsParser(int argc, char* argv[]) : is_recursive(false), is_jni(false), recursion_depth(5) {
    try {
        for (int i = 1; i < argc; ++i) {
            std::string curr(argv[i]);
            if (curr == "-h" || curr == "--help") {
                print_help();
                std::exit(0);
            } else if (curr == "-r" || curr == "--recursive") {
                is_recursive = true;
            } else if (curr == "-j" || curr == "--jni") {
                is_jni = true;
            } else if (curr == "-i" || curr == "--include") {
                include_regex.setRegex(get_next_arg(i, argc, argv, "--include"));
            } else if (curr == "-x" || curr == "--exclude") {
                exclude_regex.setRegex(get_next_arg(i, argc, argv, "--exclude"));
            } else if (curr == "-d" || curr == "--depth") {
                try {
                    recursion_depth = std::stoi(get_next_arg(i, argc, argv, "--depth"));
                    if (recursion_depth < 1) throw std::invalid_argument("--depth: invalid depth");
                }
                catch (...) { throw std::invalid_argument("--depth: invalid depth"); }
            } else if (curr == "-o" || curr == "--output") {
                out_file = get_next_arg(i, argc, argv, "--output");
            } else {
                if (!input.empty())
                    throw std::invalid_argument("Too many arguments: only one input is allowed.");
                input = curr;
            }
        }
        if (input.empty()) {
            throw std::invalid_argument("Missing input file or directory.");
        }
    }
    catch (...) {
        print_help();
        throw ;
    }
}

ArgsParser::~ArgsParser() {
}
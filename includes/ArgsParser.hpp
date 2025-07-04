#pragma once
#include <vector>
#include <string>
#include <regex>

class RegexCheck {
    private:
        std::regex regex;
        bool is_enabled = false;

    public:
        RegexCheck() = default;
        
        bool setRegex(const std::string &expression) {
            this->regex = std::regex(expression);
            this->is_enabled = true;
            return true;
        }
        
        bool matches(const std::string &class_name, const std::string &method_name) const {
            if (!is_enabled) return false;
            
            std::string comp = class_name + "." + method_name;
            return std::regex_search(comp, this->regex);
        }
        
        bool isEnabled() const { return is_enabled; }
    };

class ArgsParser
{
    private:
        std::vector<std::wstring> args;
    public:
        ArgsParser(int argc, char *argv[]);
        ~ArgsParser();

        bool is_recursive;
        bool is_jni;
        int recursion_depth;
        std::string out_file;

        RegexCheck include_regex;
        RegexCheck exclude_regex;

        std::string input;
};


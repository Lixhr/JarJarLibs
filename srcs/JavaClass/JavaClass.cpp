#include "JavaClass.hpp"
#include "GNL.hpp"

// void JavaClass::setClassData() {
//     int fd = do_sys_command_stream("javap -c -classpath " + this->jarFile + " " + this->className);
//     GNL reader(fd);

//     char *c_line = NULL;
//     for (size_t i = 0; i < 2; i ++) { // ignore head
//         char *c_line = reader.get_next_line();
//     }
    // stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    // stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');


    // string method;
    // while (getline(stream, method)) {
    //     cout << "Method : " << method << endl;
    //     stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore code:

    //     string instruction;
    //     while (getline(stream, instruction)) {
    //         if (instruction.find("return") != std::string::npos) {
    //             stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    //             break;
    //         }
    //         if (instruction.find("invoke") != std::string::npos)
    //             cout << instruction << endl;
    //     }
    // }
// }



#include "JavaClass.hpp"
#include "GNL.hpp"

JavaClass::JavaClass(std::string &className, const string &jar_file) : className(className), jarFile(jar_file) {
    if (className == "com.amazon.ebook.booklet.pdfreader.impl.PDFReflowView$3")
        this->setClassData();
}

void JavaClass::setClassData() {
    int fd = do_sys_command_stream("javap -c -classpath " + this->jarFile + " " + this->className);
    GNL reader(fd);

    for (size_t i = 0; i < 2; i ++) { // ignore head
        reader.skip_next_line();
    }

    char *c_line = NULL;
    while (!c_line || !strncmp("  public", c_line, 9)) {
        c_line = reader.get_next_line();
        free(c_line);
    }
    

    while ((c_line = reader.get_next_line()) != NULL) {
        string method(c_line);
        free(c_line);
        cout << "Method : " << method << endl;
        reader.skip_next_line();

        while ((c_line = reader.get_next_line()) != NULL) {
            string instruction(c_line);
            free(c_line);
            if (instruction.find("return") != std::string::npos) {
                reader.skip_next_line();
                break;
            }
            // if (instruction.find("invoke") != std::string::npos)
                // cout << instruction << endl;
        }
    }
}

JavaClass::~JavaClass() {
}

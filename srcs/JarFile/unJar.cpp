#include "JarFile.hpp"

void    JarFile::checkFileFormat(const string &file_name) {
    if (get_file_signature(file_name) != JAR_MAGIC) {
        throw (runtime_error("Invalid .jar magic number " + file_name));
    }
}

const filesystem::path JarFile::createFolder(const string &file_name) {
    if (!filesystem::exists(TMP_DIR)) {
        filesystem::create_directory(TMP_DIR);
    }

    filesystem::path p(file_name);
    p = TMP_DIR / p.filename().stem();

    filesystem::path final_path(p);
    size_t unique_nb = 0;

    while (filesystem::exists(final_path)) {
        ostringstream ss;
        ss << p.string() << "_" << unique_nb;
        final_path = ss.str();
        ++unique_nb;
    }

    filesystem::create_directories(final_path);
    return (final_path);
}

void    JarFile::doUnzip(const filesystem::path &dest, const string &file_name) {
    try {
        ostringstream command;

        command << "unzip " << file_name << " -d " << dest;
        int status = system(command.str().c_str());
        if (status == -1) {
            throw (runtime_error("Failed to execute unzip"));
        }
    
        if (WIFEXITED(status)) {
            int exit_code = WEXITSTATUS(status);
            if (exit_code != 0) {
                throw (runtime_error("Unzip had a problem"));
            }
            return;
        }
        throw (runtime_error("Unzip was killed"));

    }
    catch (...) {
        filesystem::remove_all(dest);
        throw;
    }
}

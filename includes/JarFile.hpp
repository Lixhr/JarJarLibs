#pragma once
#include "jjl.hpp"
#include "JniOwner.hpp"

# define JAR_MAGIC 0x504b0304

class JarFile {
    private:
        void    doUnzip(const filesystem::path &dest, const string &file_name);
        const filesystem::path  createFolder(const string &file_name);
        void    checkFileFormat(const string &file_name);
        filesystem::path    unJar(const string file_name);
        void    getClassFiles(void);

        void    fetchJNIOwners(void);
        const vector<const JniOwner *>& getJNIOwners(void);

        filesystem::path extr_folder;
        vector<ares::ClassFile> classes;

        vector<const JniOwner *> jni_owners;
    public:
        JarFile(const string);
        ~JarFile(void);
};
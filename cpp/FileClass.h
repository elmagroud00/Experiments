#ifndef FILECLASS_H
#define FILECLASS_H

#include <cstdio>
#include <stdexcept>

class FileClass {
    std::FILE* f;
public:
    struct FileClassError : std::runtime_error {
        FileClassError(const char *msg) : std::runtime_error(msg) {}
    };
    FileClass(const char *fname, const char *mode = "r");
    ~FileClass();
    std::FILE *fp();
};
#endif // FILECALSS_H ///:~

#include "file.h"

off_t retrieve_file_size(const char *name) {
    int fd = open(name, O_RDONLY);
    if (fd == -1) {
        return 0;
    }

    off_t size = lseek(fd, 0, SEEK_END);
    close(fd);
    return size;
}
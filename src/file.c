#include "file.h"

off_t retrieve_file_size(const char *name) {
    int fd = open(name, O_RDONLY);
    if (fd == -1) {
        fprintf(stderr, "fail to open file (%s): %s\n", name, strerror(errno));
        return 0;
    }

    off_t size = lseek(fd, 0, SEEK_END);
    close(fd);
    return size;
}

char *read_all_content(const char *name) {
    int fd = open(name, O_RDONLY);
    if (fd == -1) {
        return NULL;
    }

    char *content = malloc(sizeof(char) * BUF_SIZE);
    char buf[BUF_SIZE];

    ssize_t bytes_read, total_read = 0;
    while ((bytes_read = read(fd, buf, BUF_SIZE)) > 0) {
        memcpy(content + total_read, buf, bytes_read);
        total_read += bytes_read;
    }

    if (bytes_read == -1) {
        free(content);
        content = NULL;
    } else {
        char *tmp = realloc(content, sizeof(char) * (total_read + 1));
        if (content) {
            tmp[total_read] = '\0';
            content = tmp;
        }
    }

    close(fd);
    return content;
}
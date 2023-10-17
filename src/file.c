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
    char *content = NULL;

    if (name == NULL || strlen(name) == 0) {
        fprintf(stderr, "invalid file name\n");
        return content;
    }

    int fd = open(name, O_RDONLY);
    if (fd == -1) {
        fprintf(stderr, "fail to open file (%s): %s\n", name, strerror(errno));
        return content;
    }

    // file content content_size
    off_t content_size = lseek(fd, 0, SEEK_END);
    if (content_size == -1) {
        fprintf(stderr, "fail to lseek file (%s): %s\n", name, strerror(errno));
        goto out;
    }
    if (content_size == 0) {
        goto out;
    }

    // to beginning of the file
    off_t off = lseek(fd, 0, SEEK_SET);
    if (off == -1) {
        fprintf(stderr, "fail to lseek file (%s): %s\n", name, strerror(errno));
        goto out;
    }

    // content_size + 1 used to store '\0'
    size_t size = content_size + 1;

    char *tmp = malloc(sizeof(char) * size);
    if (tmp == NULL) {
        fprintf(stderr, "failed to allocate memory\n");
        goto out;
    }

    ssize_t n = read(fd, tmp, content_size);
    if (n != content_size) {
        fprintf(stderr, "fail to read file (%s): %s\n", name, strerror(errno));
        free(tmp);
        goto out;
    }

    // Add null-terminating character
    tmp[size - 1] = '\0';
    content = tmp;

out:
    close(fd);
    return content;
}
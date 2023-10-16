#pragma once

#include <memory.h>
#include <malloc.h>
#include <unistd.h>
#include <fcntl.h>

#define BUF_SIZE 256

off_t retrieve_file_size(const char *name);

char *read_all_content(const char *name);
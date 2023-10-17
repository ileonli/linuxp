#pragma once

#include <errno.h>
#include <fcntl.h>
#include <malloc.h>
#include <memory.h>
#include <unistd.h>

off_t retrieve_file_size(const char *name);

char *read_all_content(const char *name);
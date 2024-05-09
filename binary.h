#ifndef _BINARY_H
#define _BINARY_H
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

int is_txt_file(const char *filename);
void bin_to_txt(const char* binaryFilePath, const char* textFilePath);

#endif

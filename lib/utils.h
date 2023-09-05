//
// Created by Alessio Gjergji on 05/09/23.
//

#ifndef PNGANALYZER_UTILS_H
#define PNGANALYZER_UTILS_H

#include <stdio.h>
#include <string.h>
#include "assert.h"
#include "errno.h"
#include "stdlib.h"


/*****************Public functions******************/
void read_bytes_or_panic(FILE * file, void *buf, size_t buf_cap);

void print_bytes(uint8_t *buf, size_t buf_cap);

void reverse_bytes(void *buf, size_t buf_cap);

#endif //PNGANALYZER_UTILS_H

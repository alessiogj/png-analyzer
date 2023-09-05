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
/**
 * Read bytes from file or panic
 * @param file file to read from
 * @param buf buffer to fill
 * @param buf_cap size of the buffer
 */
void read_bytes_or_panic(FILE * file, void *buf, size_t buf_cap);

/**
 * Print bytes
 * @param buf buffer to print
 * @param buf_cap size of the buffer
 */
void print_bytes(uint8_t *buf, size_t buf_cap);

/**
 * Reverse bytes
 * @param buf buffer to reverse
 * @param buf_cap size of the buffer
 */
void reverse_bytes(void *buf, size_t buf_cap);

#endif //PNGANALYZER_UTILS_H

//
// Created by Alessio Gjergji on 05/09/23.
//

#ifndef PNGANALYZER_IHDR_ANALYZER_H
#define PNGANALYZER_IHDR_ANALYZER_H

#include "types.h"
#include "utils.h"

/**
 * Parse the IHDR chunk
 * @param input_file file to read from
 * @param header header struct to fill
 * @param bit_per_pixel bit per pixel
 */
void parse_ihdr(FILE* input_file, png_header_ihdr_t *header, int16_t *bit_per_pixel);


#endif //PNGANALYZER_IHDR_ANALYZER_H

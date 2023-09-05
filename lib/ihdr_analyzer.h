//
// Created by Alessio Gjergji on 05/09/23.
//

#ifndef PNGANALYZER_IHDR_ANALYZER_H
#define PNGANALYZER_IHDR_ANALYZER_H

#include "types.h"
#include "utils.h"

void parse_ihdr(FILE* input_file, png_header_ihdr_t *header, int16_t *bit_per_pixel);


#endif //PNGANALYZER_IHDR_ANALYZER_H

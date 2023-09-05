//
// Created by Alessio Gjergji on 05/09/23.
//

#ifndef PNGANALYZER_IDAT_ANALYZER_H
#define PNGANALYZER_IDAT_ANALYZER_H

#include "../lib/types.h"
#include "../lib/utils.h"
#include <zlib.h>

/**
 * Parse the IDAT chunk
 * @param input_file file to read from
 * @param chunk_sz size of the chunk
 */
void parse_idat(FILE* input_file, int32_t chunk_sz);

#endif //PNGANALYZER_IDAT_ANALYZER_H

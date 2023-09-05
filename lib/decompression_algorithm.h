//
// Created by Alessio Gjergji on 05/09/23.
//

#ifndef PNGANALYZER_DECOMPRESSION_ALGORITHM_H
#define PNGANALYZER_DECOMPRESSION_ALGORITHM_H

#include "types.h"
#include "utils.h"
#include <zlib.h>

uint8_t *decompress(uint8_t *src, uint32_t size, uint32_t *result_sz);

#endif //PNGANALYZER_DECOMPRESSION_ALGORITHM_H

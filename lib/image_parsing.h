//
// Created by Alessio Gjergji on 05/09/23.
//

#ifndef PNGANALYZER_IMAGE_PARSING_H
#define PNGANALYZER_IMAGE_PARSING_H
#include "../lib/types.h"
#include "../lib/utils.h"

color_channels_t parse_image(uint32_t *buf, png_header_ihdr_t header);
void print_histogram_rgba(rgba_channels_t colors_channels);
#endif //PNGANALYZER_IMAGE_PARSING_H

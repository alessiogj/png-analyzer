//
// Created by Alessio Gjergji on 05/09/23.
//

#ifndef PNGANALYZER_TYPES_H
#define PNGANALYZER_TYPES_H

// IHDR structure
#pragma pack(push, 1)  // Imposta l'allineamento su 1 byte

#include <stdint.h>
#include "stdbool.h"

typedef struct {
    uint32_t width;             //image dimension in pixel
    uint32_t height;            //image dimension in pixel
    uint8_t bit_depth;          //number of the bits per sample or per palette index
    uint8_t  color_type;        //
    uint8_t compression_method;
    uint8_t filter_method;
    uint8_t interlace_method;
} png_header_ihdr_t;
#pragma pack(pop)  // Ripristina l'allineamento predefinito

// IDAT structure
#pragma pack(push, 1)  // Imposta l'allineamento su 1 byte
typedef struct {
    //TODO
}png_header_idat_t;
#pragma pack(pop)  // Ripristina l'allineamento predefinito

//Color types
typedef enum {
    PNG_COLOR_TYPE_GRAYSCALE = 0,
    PNG_COLOR_TYPE_RGB = 2,
    PNG_COLOR_TYPE_PALETTE = 3,
    PNG_COLOR_TYPE_GRAYSCALE_ALPHA = 4,
    PNG_COLOR_TYPE_RGBA = 6
}png_color_type;

#endif //PNGANALYZER_TYPES_H

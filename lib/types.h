//
// Created by Alessio Gjergji on 05/09/23.
//

#ifndef PNGANALYZER_TYPES_H
#define PNGANALYZER_TYPES_H

#include <stdint.h>
#include "stdbool.h"

#pragma pack(push, 1)           // exact fit - no padding
typedef struct {
    uint32_t width;             //image dimension in pixel
    uint32_t height;            //image dimension in pixel
    uint8_t bit_depth;          //number of the bits per sample or per palette index
    uint8_t  color_type;        //color type of the image
    uint8_t compression_method; //compression method of the image
    uint8_t filter_method;      //filter method of the image
    uint8_t interlace_method;   //interlace method of the image
} png_header_ihdr_t;
#pragma pack(pop)               //back to whatever the previous packing mode was

// IDAT structure
#pragma pack(push, 1)           // exact fit - no padding
typedef struct {
    //TODO
}png_header_idat_t;
#pragma pack(pop)               //back to whatever the previous packing mode was

//Color type
typedef enum {
    PNG_COLOR_TYPE_GRAYSCALE = 0,
    PNG_COLOR_TYPE_RGB = 2,
    PNG_COLOR_TYPE_PALETTE = 3,
    PNG_COLOR_TYPE_GRAYSCALE_ALPHA = 4,
    PNG_COLOR_TYPE_RGBA = 6
}png_color_type;

#endif //PNGANALYZER_TYPES_H

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

typedef struct  {
    uint32_t color;
    uint32_t count;
    uint32_t pixel;
}color_count_t;

typedef struct {
    color_count_t unique_colors_r[256];
    color_count_t unique_colors_g[256];
    color_count_t unique_colors_b[256];
    color_count_t unique_colors_a[256];
}rgba_channels_t;

typedef struct {
    color_count_t unique_colors_r[256];
    color_count_t unique_colors_g[256];
    color_count_t unique_colors_b[256];
}rgb_channels_t;

typedef struct {
    color_count_t unique_colors_greyscale[256];
    color_count_t unique_colors_a[256];
}greyscale_alpha_channels_t;

typedef struct {
    color_count_t unique_colors_greyscale[256];
}greyscale_channels_t;

typedef union {
    greyscale_channels_t greyscale_channels;
    rgb_channels_t rgb_channels;
    greyscale_alpha_channels_t greyscale_alpha_channels;
    rgba_channels_t rgba_channels;
}color_channels_t;

//Color type
typedef enum {
    PNG_COLOR_TYPE_GRAYSCALE = 0,
    PNG_COLOR_TYPE_RGB = 2,
    PNG_COLOR_TYPE_PALETTE = 3,
    PNG_COLOR_TYPE_GRAYSCALE_ALPHA = 4,
    PNG_COLOR_TYPE_RGBA = 6
}png_color_type;

#endif //PNGANALYZER_TYPES_H

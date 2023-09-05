//
// Created by Alessio Gjergji on 05/09/23.
//
#include "../lib/ihdr_analyzer.h"

void parse_ihdr(FILE* input_file, png_header_ihdr_t *header, int16_t *bit_per_pixel)
{
    printf("/*---------------------------------------------------------------------*\n");
    printf(" *                                                                     *\n");
    printf(" *                         Analysis of IHDR                            *\n");
    printf(" *                                                                     *\n");
    printf(" * --------------------------------------------------------------------*/\n");
    read_bytes_or_panic(input_file, header, sizeof(png_header_ihdr_t));

    //width and height
    reverse_bytes(&header->width, sizeof(header->width));
    reverse_bytes(&header->height, sizeof(header->height));
    printf("Width is: %d\n", header->width);
    printf("Height is: %d\n", header->height);

    //bits depth
    printf("The bit depth is: %d\n", header->bit_depth);

    //Color type
    switch (header->color_type)
    {
        case PNG_COLOR_TYPE_GRAYSCALE:
            printf("Color type: Grayscale\n");
            *bit_per_pixel = header->bit_depth;
            break;
        case PNG_COLOR_TYPE_RGB:
            printf("Color type: Truecolor (RGB)\n");
            *bit_per_pixel = header->bit_depth * 3;
            break;
        case PNG_COLOR_TYPE_PALETTE:
            printf("Color type: Indexed color\n");
            *bit_per_pixel = header->bit_depth;
            break;
        case PNG_COLOR_TYPE_GRAYSCALE_ALPHA:
            printf("Color type: Grayscale with Alpha\n");
            *bit_per_pixel = header->bit_depth * 2;
            break;
        case PNG_COLOR_TYPE_RGBA:
            printf("Color type: Truecolor with Alpha (RGBA)\n");
            *bit_per_pixel = header->bit_depth * 4;
            break;
        default:
            printf("Color type undefined\n");
            fprintf(stderr, "ERROR: could define the color type: %s\n", strerror(errno));
            fclose(input_file);
            exit(1);
    }

    //bit per pixel
    printf("Bit per pixel are: %d\n", *bit_per_pixel);

    printf("The filter method is: %d\n", header->filter_method);

    printf("The Interlace method is: %d\n", header->interlace_method);

    //Compression method
    if (header->compression_method != 0)
    {
        printf("Compression is: %d\n", header->compression_method);
        fprintf(stderr, "ERROR: standard PNG requires standard compression");
        fclose(input_file);
        exit(1);
    }
}

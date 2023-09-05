//
// Created by Alessio Gjergji on 05/09/23.
//
#include "../lib/image_parsing.h"

rgba_channels_t parse_rgba(uint32_t *buf, uint32_t width, uint32_t height);
rgb_channels_t parse_rgb(uint32_t *buf, uint32_t width, uint32_t height);
greyscale_channels_t parse_greyscale(uint32_t *buf, uint32_t width, uint32_t height);
greyscale_alpha_channels_t parse_greyscale_alpha(uint32_t *buf, uint32_t width, uint32_t height);

color_channels_t parse_image(uint32_t *buf, png_header_ihdr_t header)
{
    color_channels_t res;
    switch (header.color_type) {
        case PNG_COLOR_TYPE_GRAYSCALE:
            res.greyscale_channels = parse_greyscale(buf, header.width, header.height);
            return res;
        case PNG_COLOR_TYPE_RGB:
            res.rgb_channels = parse_rgb(buf, header.width, header.height);
            return res;
        case PNG_COLOR_TYPE_PALETTE:
            res.rgb_channels = parse_rgb(buf, header.width, header.height);
            return res;
        case PNG_COLOR_TYPE_GRAYSCALE_ALPHA:
            res.greyscale_alpha_channels = parse_greyscale_alpha(buf, header.width, header.height);
            return res;
        case PNG_COLOR_TYPE_RGBA:
            res.rgba_channels = parse_rgba(buf, header.width, header.height);
            return res;
    }
}

void print_histogram_rgba(rgba_channels_t colors_channels)
{
    printf("Histogram for Channel R:\n");
    for (int i = 0; i < 256; i++) {
        if (colors_channels.unique_colors_r[i].count > 0) {
            printf("%d: ",  colors_channels.unique_colors_r[i].color);
            for (int j = 0; j <  colors_channels.unique_colors_r[i].count; j++) {
                printf("*");
            }
            printf("\n");
        }
    }
    printf("Histogram for Channel G:\n");
    for (int i = 0; i < 256; i++) {
        if (colors_channels.unique_colors_g[i].count > 0) {
            printf("%d: ", colors_channels.unique_colors_g[i].color);
            for (int j = 0; j < colors_channels.unique_colors_g[i].count; j++) {
                printf("*");
            }
            printf("\n");
        }
    }
    printf("Histogram for Channel B:\n");
    for (int i = 0; i < 256; i++) {
        if (colors_channels.unique_colors_b[i].count > 0) {
            printf("%d: ", colors_channels.unique_colors_b[i].color);
            for (int j = 0; j < colors_channels.unique_colors_b[i].count; j++) {
                printf("*");
            }
            printf("\n");
        }
    }
    printf("Histogram for Channel A:\n");
    for (int i = 0; i < 256; i++) {
        if (colors_channels.unique_colors_a[i].count > 0) {
            printf("%d: ", colors_channels.unique_colors_a[i].color);
            for (int j = 0; j < colors_channels.unique_colors_a[i].count; j++) {
                printf("*");
            }
            printf("\n");
        }
    }
}

rgb_channels_t parse_rgb(uint32_t *buf, uint32_t width, uint32_t height)
{
    //TODO: implement
    rgb_channels_t val;
    return val;
}

greyscale_channels_t parse_greyscale(uint32_t *buf, uint32_t width, uint32_t height)
{
    //TODO: implement
    greyscale_channels_t val;
    return val;
}

greyscale_alpha_channels_t parse_greyscale_alpha(uint32_t *buf, uint32_t width, uint32_t height)
{
    //TODO: implement
    greyscale_alpha_channels_t val;
    return val;
}

rgba_channels_t parse_rgba(uint32_t *buf, uint32_t width, uint32_t height)
{
    rgba_channels_t colors_channels;

    //initialize the array
    for (int i = 0; i < 256; i++) {
        colors_channels.unique_colors_r[i].color = (uint8_t)i;
        colors_channels.unique_colors_r[i].count = 0;
        colors_channels.unique_colors_r[i].pixel = 0;
        colors_channels.unique_colors_g[i].color = (uint8_t)i;
        colors_channels.unique_colors_g[i].count = 0;
        colors_channels.unique_colors_g[i].pixel = 0;
        colors_channels.unique_colors_b[i].color = (uint8_t)i;
        colors_channels.unique_colors_b[i].count = 0;
        colors_channels.unique_colors_b[i].pixel = 0;
        colors_channels.unique_colors_a[i].color = (uint8_t)i;
        colors_channels.unique_colors_a[i].count = 0;
        colors_channels.unique_colors_a[i].pixel = 0;
    }

    //count the unique colors for each channel
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            uint32_t pixel = buf[y * width + x];
            uint8_t r = (pixel >> 24) & 0xFF;
            uint8_t g = (pixel >> 16) & 0xFF;
            uint8_t b = (pixel >> 8) & 0xFF;
            uint8_t a = pixel & 0xFF;

            colors_channels.unique_colors_r[r].count++;
            colors_channels.unique_colors_g[g].count++;
            colors_channels.unique_colors_b[b].count++;
            colors_channels.unique_colors_a[a].count++;

            colors_channels.unique_colors_r[r].pixel = x + y;
            colors_channels.unique_colors_g[g].pixel = x + y;
            colors_channels.unique_colors_b[b].pixel = x + y;
            colors_channels.unique_colors_a[a].pixel = x + y;
        }
    }
    return colors_channels;
}




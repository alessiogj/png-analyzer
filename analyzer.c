#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "assert.h"
#include "stdint.h"
#include "stdbool.h"
#include "errno.h"

#define  PNG_SIG_CAP    8
#define  IEND           0x444E4549
#define  IDAT           0x54414449
#define  IHDR           0x52444849

uint8_t  png_sig[] = {137, 80, 78, 71, 13, 10, 26, 10};


// IHDR structure
typedef struct {
    uint32_t width;             //image dimension in pixel
    uint32_t height;            //image dimension in pixel
    uint8_t bit_depth;          //number of the bits per sample or per palette index
    uint8_t  color_type;        //
    uint8_t compression_method;
    uint8_t filter_method;
    uint8_t interlace_method;
} png_header_t;

//Color types
typedef enum {
    PNG_COLOR_TYPE_GRAYSCALE = 0,
    PNG_COLOR_TYPE_RGB = 2,
    PNG_COLOR_TYPE_PALETTE = 3,
    PNG_COLOR_TYPE_GRAYSCALE_ALPHA = 4,
    PNG_COLOR_TYPE_RGBA = 6
}png_color_type;

void read_bytes_or_panic(FILE * file, void *buf, size_t buf_cap)
{
    size_t n = fread(buf, buf_cap, 1, file);
    if (n != 1) {
        if (ferror(file))
        {
            fprintf(stderr, "ERROR: could not read %zu bytes from file: %s\n", strerror(errno));
            exit(1);
        }
        else if (feof(file))
        {
            fprintf(stderr, "ERROR: could not read %zu bytes from file: reached the end of file\n");
            exit(1);
        }
        else
        {
            assert(0 && "unreachable");
        }
    }
}

void print_bytes(uint8_t *buf, size_t buf_cap)
{
    for (size_t  i = 0; i < buf_cap; i++)
    {
        printf("%u ", buf[i]);
    }
    printf("\n");
}

void reverse_bytes(void *buf, size_t buf_cap)
{
    uint8_t *buf_uint8 = buf;
    for(size_t i = 0; i < buf_cap/2; ++i)
    {
        uint8_t t = buf_uint8[i];
        buf_uint8[i] = buf_uint8[buf_cap - i - 1];
        buf_uint8[buf_cap - i - 1] = t;
    }
}

int main(int argc, char **argv)
{
    (void) argc;
    assert(*argv != NULL);
    char *program = *argv++;

    if (*argv == NULL)
    {
        printf("Usage: %s <input.png>\n", program);
        fprintf(stderr, "ERROR: no input file is provided\n", program);
        exit(1);
    }

    char *input_filepath = *argv++;
    printf("Inspected file is %s\n", input_filepath);

    FILE *input_file = fopen(input_filepath, "rb");
    if (input_file == NULL)
    {
        fprintf(stderr, "ERROR: could not open file %s: %s\n", input_filepath, strerror(errno));
        exit(1);
    }
    /*----------------------------------------------------------------------------------------*
     *                                                                                        *
     *                                  SIGNATURE                                             *
     *                                                                                        *
     * ---------------------------------------------------------------------------------------*/

    uint8_t  sig[PNG_SIG_CAP];
    read_bytes_or_panic(input_file, sig, PNG_SIG_CAP);
    printf("Signature: ");
    print_bytes(sig, PNG_SIG_CAP);
    if (memcmp(sig, png_sig, PNG_SIG_CAP) != 0) {
        fprintf(stderr, "ERROE: %s does not appear to be a valid PNG image\n", input_filepath);
        exit(1);
    }

    /*----------------------------------------------------------------------------------------*
     *                                                                                        *
     *                                     CHUNK                                              *
     *                                                                                        *
     * ---------------------------------------------------------------------------------------*/

    bool quit = false;
    png_header_t header;
    int16_t bit_per_pixel;

    while(!quit)
    {
        //chunk size
        uint32_t chunk_sz;
        read_bytes_or_panic(input_file, &chunk_sz, sizeof(chunk_sz));
        reverse_bytes(&chunk_sz, sizeof chunk_sz);


        //chunk type
        uint8_t chunk_type[4];
        read_bytes_or_panic(input_file, chunk_type, sizeof (chunk_type));

        if (*(uint32_t *)chunk_type == IEND)
        {
            quit = true;
        }
        else if (*(uint32_t *)chunk_type == IHDR)
        {

            read_bytes_or_panic(input_file, &header, sizeof(png_header_t));

            //width and height
            reverse_bytes(&header.width, sizeof(header.width));
            reverse_bytes(&header.height, sizeof(header.height));
            printf("Width is: %d\n", header.width);
            printf("Height is: %d\n", header.height);

            //bits depth
            printf("The bit depth is: %d\n", header.bit_depth);

            //Color type
            switch (header.color_type)
            {
                case PNG_COLOR_TYPE_GRAYSCALE:
                    printf("Color type: Grayscale\n");
                    bit_per_pixel = header.bit_depth;
                    break;
                case PNG_COLOR_TYPE_RGB:
                    printf("Color type: Truecolor (RGB)\n");
                    bit_per_pixel = header.bit_depth * 3;
                    break;
                case PNG_COLOR_TYPE_PALETTE:
                    printf("Color type: Indexed color\n");
                    bit_per_pixel = header.bit_depth;
                    break;
                case PNG_COLOR_TYPE_GRAYSCALE_ALPHA:
                    printf("Color type: Grayscale with Alpha\n");
                    bit_per_pixel = header.bit_depth * 2;
                    break;
                case PNG_COLOR_TYPE_RGBA:
                    printf("Color type: Truecolor with Alpha (RGBA)\n");
                    bit_per_pixel = header.bit_depth * 4;
                    break;
                default:
                    printf("Color type undefined\n");
                    fprintf(stderr, "ERROR: could define the color type: %s\n", strerror(errno));
                    exit(1);
            }

            //bit per pixel
            printf("Bit per pixel are: %d\n", bit_per_pixel);


            /*! TODO: da analizzare */
            printf("The filter method is: %d\n", header.filter_method);

            printf("The Interlace method is: %d\n", header.interlace_method);

            //Compression method
            if (header.compression_method != 0)
            {
                printf("Compression is: %d\n", header.compression_method);
                fprintf(stderr, "ERROR: standard PNG requires standard compression");
                exit(1);
            }

            chunk_sz -= sizeof(header);
        }


        if(fseek(input_file, chunk_sz, SEEK_CUR) < 0)
        {
            fprintf(stderr, "ERROR: could not skip a chunk: %s\n", strerror(errno)) ;
            exit(1);
        }

        uint32_t chunk_crc;
        read_bytes_or_panic(input_file, &chunk_crc, sizeof(chunk_crc));

        printf("Chunk size: %d\n", chunk_sz);
        printf("Chunk type: %.*s (0x%08X)\n", (int)sizeof(chunk_type), chunk_type, *(uint32_t *)chunk_type);
        printf("Chunk CRC: 0x%08X\n", chunk_crc);
        printf("---------------------------------------------------------\n");
    }



    fclose(input_file);

    return 0;
}

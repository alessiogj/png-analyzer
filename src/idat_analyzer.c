//
// Created by Alessio Gjergji on 05/09/23.
//

#include "../lib/idat_analyzer.h"
#include "../lib/decompression_algorithm.h"
#include "../lib/types.h"
#include "../lib/image_parsing.h"

/*********************************public functions********************************/
void parse_idat(FILE* input_file, uint32_t chunk_sz, png_header_ihdr_t header)
{
    printf("/*---------------------------------------------------------------------*\n");
    printf(" *                                                                     *\n");
    printf(" *                         Analysis of IDAT                            *\n");
    printf(" *                                                                     *\n");
    printf(" * --------------------------------------------------------------------*/\n");
    printf("data length is: %d bytes\n", chunk_sz);

    unsigned char compressed_data[chunk_sz];
    read_bytes_or_panic(input_file, &compressed_data, sizeof(compressed_data));

    uint32_t result_sz = 0;
    uint32_t *decompressed_data = decompress(compressed_data, chunk_sz, &result_sz);

    /*TODO: ho supposto che l'immagine sia RGBA, generalizzare in modo da poter ritornare una struttura
     * dinamica a seconda del contesto, il valore della struttura è parametrica ai canali presenti nell'immagine*/

    color_channels_t colors = parse_image(decompressed_data, header);
    switch (header.color_type) {
        case PNG_COLOR_TYPE_GRAYSCALE:
            break;
        case PNG_COLOR_TYPE_RGB:
            break;
        case PNG_COLOR_TYPE_PALETTE:
            break;
        case PNG_COLOR_TYPE_GRAYSCALE_ALPHA:
            break;
        case PNG_COLOR_TYPE_RGBA:
            print_histogram_rgba(colors.rgba_channels);
            break;
    }

    free(decompressed_data);
}

/*********************************private functions********************************/

//
// Created by Alessio Gjergji on 05/09/23.
//

#include "../lib/idat_analyzer.h"
#include "../lib/decompression_algorithm.h"

/*********************************public functions********************************/
void parse_idat(FILE* input_file, int32_t chunk_sz)
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
    unsigned char *decompressed_data = decompress(compressed_data, chunk_sz, &result_sz);

    for(int i = 0; i < result_sz; i++)
    {
        printf("%u", decompressed_data[i]);
        if (i % 800 == 0)
            printf("\n");
    }
    printf("\n");

    free(decompressed_data);

}

/*********************************private functions********************************/

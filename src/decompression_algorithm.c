//
// Created by Alessio Gjergji on 05/09/23.
//

#include "../lib/decompression_algorithm.h"

uint8_t *decompress(uint8_t *src, uint32_t size, uint32_t *result_sz)
{
    z_stream stream;
    stream.zalloc = Z_NULL;
    stream.zfree = Z_NULL;
    stream.opaque = Z_NULL;
    stream.avail_in = size;
    stream.next_in = src;

    unsigned char *decompressed_data = NULL;
    size_t decompressed_size = 0;
    size_t allocated_size = 0;

    int32_t inflate_result = inflateInit(&stream);
    if (inflate_result != Z_OK) {
        fprintf(stderr, "Errore nell'inizializzazione dello stream di decompressione: %s\n", stream.msg);
        exit(1);
    }

    while (1) {
        // Alloca dinamicamente più memoria se necessario
        if (decompressed_size + size > allocated_size) {
            allocated_size += size;
            decompressed_data = (unsigned char *)realloc(decompressed_data, allocated_size);
            if (decompressed_data == NULL) {
                fprintf(stderr, "Errore: impossibile allocare memoria per i dati decompressi\n");
                inflateEnd(&stream);
                exit(1);
            }
        }

        stream.avail_out = size;
        stream.next_out = decompressed_data + decompressed_size;

        int32_t inflate_result = inflate(&stream, Z_NO_FLUSH);
        if (inflate_result == Z_STREAM_END) {
            break; // Fine della decompressione
        }
        if (inflate_result != Z_OK) {
            fprintf(stderr, "Errore durante la decompressione dei dati: %s\n", stream.msg);
            free(decompressed_data);
            inflateEnd(&stream);
            exit(1);
        }

        decompressed_size += size;
    }

    inflateEnd(&stream);

    *result_sz =  *result_sz = stream.total_out;;
    return decompressed_data;
}
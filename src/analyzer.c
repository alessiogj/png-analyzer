#include "../lib/utils.h"
#include "../lib/types.h"
#include "../lib/idat_analyzer.h"
#include "../lib/ihdr_analyzer.h"

#define  PNG_SIG_CAP    8
#define  IEND           0x444E4549
#define  IDAT           0x54414449
#define  IHDR           0x52444849

uint8_t  png_sig[] = {137, 80, 78, 71, 13, 10, 26, 10};

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
        fclose(input_file);
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
        fclose(input_file);
        exit(1);
    }

    /*----------------------------------------------------------------------------------------*
     *                                                                                        *
     *                                     CHUNK                                              *
     *                                                                                        *
     * ---------------------------------------------------------------------------------------*/

    bool quit = false;
    png_header_ihdr_t header;
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
            //TODO: dopo il parsing rimuovere la fseek
            if(fseek(input_file, chunk_sz, SEEK_CUR) < 0)
            {
                fprintf(stderr, "ERROR: could not skip a chunk: %s\n", strerror(errno));
                fclose(input_file);
                exit(1);
            }
            printf("------------------------------------------------------------------------\n");
        }
        else if (*(uint32_t *)chunk_type == IHDR)
        {
            parse_ihdr(input_file, &header, &bit_per_pixel);
        }
        else
        {
            parse_idat(input_file, chunk_sz);
            //TODO: dopo il parsing rimuovere la fseek
            /*if(fseek(input_file, chunk_sz, SEEK_CUR) < 0)
            {
                fprintf(stderr, "ERROR: could not skip a chunk: %s\n", strerror(errno)) ;
                fclose(input_file);
                exit(1);
            }*/
        }

        uint32_t chunk_crc;
        read_bytes_or_panic(input_file, &chunk_crc, sizeof(chunk_crc));

        printf("Chunk CRC: 0x%08X\n", chunk_crc);
    }

    fclose(input_file);

    return 0;
}

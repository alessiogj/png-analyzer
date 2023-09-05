//
// Created by Alessio Gjergji on 05/09/23.
//

#include "../lib/types.h"
#include "../lib/utils.h"



void read_bytes_or_panic(FILE * file, void *buf, size_t buf_cap)
{
    size_t n = fread(buf, buf_cap, 1, file);
    if (n != 1) {
        if (ferror(file))
        {
            fprintf(stderr, "ERROR: could not read %zu bytes from file: %s\n", strerror(errno));
            fclose(file);
            exit(1);
        }
        else if (feof(file))
        {
            fprintf(stderr, "ERROR: could not read %zu bytes from file: reached the end of file\n");
            fclose(file);
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
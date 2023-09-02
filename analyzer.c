#include <stdio.h>
#include <stdlib.h>
#include "assert.h"
#include "errno.h"

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

    return 0;
}

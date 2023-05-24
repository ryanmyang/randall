#include "options.h"
#include <stdbool.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void parse_options(struct options *o, int argc, char **argv) {
    if (argc == 2 || argc==4)
    {
        char *endptr;
        errno = 0;
        o->nbytes = strtoll(argv[1], &endptr, 10);
        if (errno)
            perror(argv[1]);
        else
            o->valid = !*endptr && 0 <= o->nbytes;

        if (argc == 4 && strcmp(argv[2], "-i") == 0) {
            o->input_option = 0;
            handle_input(o, argv[3]);
        }
    }

    // Error if wrong number of arguments
    else
    {
        fprintf(stderr, "%s: usage: %s NBYTES\n", argv[0], argv[0]);
        fprintf(stderr, "%s: usage: %s NBYTES -i [OPTION] \n", argv[0], argv[0]);
        o->valid = false;
    }

}

void handle_input(struct options *o, char *input)
{

    if (strcmp(input, "rdrand") == 0)
    {
        return;
    }
    else if (input[0] == '/' && strlen(input) > 1)
    {
        o->input_option = 2;
        o->file = input;
    }
    else if (strcmp(input, "mrand48_r") == 0)
    {
        o->input_option = 1;
    }
    else {
        o->valid = false;
        o-> input_option = -1;
    }
}

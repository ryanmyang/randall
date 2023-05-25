#include "options.h"
#include "rand64-sw.h"
#include "output.h"
#include <stdbool.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int is_positive_integer(const char *str) {
    if (str == NULL || *str == '\0') {
        return 0;
    }

    while (*str != '\0') {
        if (!isdigit(*str)) {
            return 0;
        }
        ++str;
    }

    return 1;
}


void handle_input(struct options *o, char *input)
{
    // printf("handling input");
    if (strcmp(input, "rdrand") == 0)
    {
        return;
    }
    else if (input[0] == '/' && strlen(input) > 1)
    {
        // printf("detected slash");
        o->input_option = 2;
        // o->file = input;
        // printf("file: %s", o->file);
        // printf("about to set file as input");
        set_file(input);
    }
    else if (strcmp(input, "mrand48_r") == 0)
    {
        o->input_option = 1;
    }
    else
    {
        o->valid = false;
        o->input_option = -1;
    }
    // printf("handled input");
}

void handle_output(struct options *o, char *output)
{
    // printf("handling output");
    if (strcmp(output, "stdio") == 0)
    {
        o->output_option = 0;
    }
    else if (is_positive_integer(output)==1)
    {
        // printf("pos int");

        o->output_option = 1;
        set_buffer_size(atoi(output));
    }
    else {
        o->valid = false;
        o->output_option = -1;
    }
    
}

void parse_options(struct options *o, int argc, char **argv) {
    // printf("parsing options");
    if (argc == 2 || argc==4 || argc==6)
    {
        char *endptr;
        errno = 0;
        o->nbytes = strtoll(argv[1], &endptr, 10);
        if (errno)
            perror(argv[1]);
        else
            o->valid = !*endptr && 0 <= o->nbytes;
        o->input_option = 0;

        if (argc == 4 || argc == 6) {

            // First validate the 3rd and fourth argument
            if (strcmp(argv[2], "-i") == 0){
                handle_input(o, argv[3]);
            }
            else if (strcmp(argv[2], "-o")==0) {
                handle_output(o, argv[3]);
            }
            else {
                o->valid=false;
                return;
            }
            // If fifth and sixth argument, validate those too

            if(argc==6) {
                if (strcmp(argv[4], "-i") == 0)
                {
                    handle_input(o, argv[5]);
                }
                else if (strcmp(argv[4], "-o") == 0)
                {
                    handle_output(o, argv[5]);
                }
                else
                {
                    printf("invalid arg6");
                    o->valid = false;
                    return;
                }
            }
        }
    }
    else
    {
        o->valid = false;
    }

}

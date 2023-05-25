#ifndef OPTIONS_H
#define OPTIONS_H
#include <stdbool.h>

struct options {
    bool valid;
    long long nbytes;
    int input_option;
    int output_option;
    char* file;
    int write_bytes;
};

void parse_options(struct options *o, int argc, char **argv);
void handle_input(struct options *o, char *input);
void handle_output(struct options *o, char *output);

#endif

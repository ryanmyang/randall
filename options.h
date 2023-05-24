#ifndef OPTIONS_H
#define OPTIONS_H
#include <stdbool.h>

struct options {
    bool valid;
    long long nbytes;
    int input_option;
    char* file;
};

void parse_options(struct options *o, int argc, char **argv);
void handle_input(struct options *o, char *input);

#endif

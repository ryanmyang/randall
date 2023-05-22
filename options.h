#ifndef OPTIONS_H
#define OPTIONS_H
#include <stdbool.h>

struct options {
    bool valid;
    long long nbytes;
};

void parse_options(struct options *o, int argc, char **argv);

#endif

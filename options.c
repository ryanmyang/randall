#include "options.h"
#include <stdbool.h>
#include <errno.h>

void parse_options(struct options *o, int argc, char **argv) {
    if (argc == 2)
    {
        char *endptr;
        errno = 0;
        o->nbytes = strtoll(argv[1], &endptr, 10);
        if (errno)
            perror(argv[1]);
        else
            o->valid = !*endptr && 0 <= o->nbytes;
    }
    
}

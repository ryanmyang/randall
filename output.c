#include "output.h"
#include <stdio.h>
#include <limits.h>
#include <unistd.h>
#include <stdlib.h>

static int output_mode = 0;
static unsigned char *output_buffer = NULL;
static int output_buffer_size = 0;

void set_buffer_size(int size) {
    output_buffer_size = size;
}

bool writebytes(unsigned long long x, int nbytes)
{
    if (output_mode==0)
    {
    do
    {
        if (putchar(x) < 0)
            return false;
        x >>= CHAR_BIT;
        nbytes--;
    } while (0 < nbytes);
    }
    else
    {
    // Write mode for N bytes
    if (output_buffer == NULL)
    {
        // Allocate the output buffer
        output_buffer_size = nbytes;
        output_buffer = (unsigned char *)malloc(output_buffer_size);
        if (output_buffer == NULL)
            return false;
    }
    else if (output_buffer_size < nbytes)
    {
        // Reallocate the output buffer if the size is not enough
        output_buffer_size = nbytes;
        output_buffer = (unsigned char *)realloc(output_buffer, output_buffer_size);
        if (output_buffer == NULL)
            return false;
    }

    unsigned char *ptr = output_buffer;
    for (int i = 0; i < nbytes; i++)
    {
        *ptr++ = x & 0xFF;
        x >>= CHAR_BIT;
    }

    int total_bytes_written = 0;
    while (total_bytes_written < nbytes)
    {
        int bytes_written=write(1,output_buffer +total_bytes_written,nbytes -total_bytes_written);
        if (bytes_written < 0)
            return false;
        total_bytes_written += bytes_written;
    }
    }
    return true;
}

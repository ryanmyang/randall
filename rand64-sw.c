#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "rand64-sw.h"


/* Input stream containing random bytes.  */
static FILE *urandstream;

void set_file(char *file) {
    // printf("setting file");
    urandstream = fopen(file, "r");
    if (!urandstream) {
        fprintf(stderr,"fopen urandstream failed for %s", file);
        abort();
    }
}

    /* Initialize the software rand64 implementation.  */
void software_rand64_init(void)
{
    
}

/* Return a random value, using software operations.  */
unsigned long long
software_rand64(void)
{
    unsigned long long int x;

    // if mrand48_r
    // x = mrand48_r()

    if (fread(&x, sizeof x, 1, urandstream) != 1) {
        fprintf(stderr, "fread urandstream failed");
        abort();

    }


    return x;
}

/* Finalize the software rand64 implementation.  */
void
software_rand64_fini(void)
{
    fclose(urandstream);
}


// Init mrand48

static struct drand48_data randomBuffer;

// Function to initialize the random number generator
void software_mrand48_init()
{
    FILE *randomFile = fopen("/dev/random", "rb");
    if (randomFile == NULL)
    {
        perror("Failed to open /dev/random");
        abort();
    }

    unsigned short seed[3];
    size_t bytesRead = fread(seed, sizeof(unsigned short), 3, randomFile);
    if (bytesRead != 3)
    {
        perror("Failed to read from /dev/random");
        fclose(randomFile);
        abort();
    }

    fclose(randomFile);

    // Seed the random number generator
    seed48_r(seed, &randomBuffer);
}

// Function to generate a random long long
unsigned long long software_mrand48()
{
    unsigned long randomValue;
    mrand48_r(&randomBuffer, (long *)&randomValue);
    // printf("mrand48 randomValue: %d \n", randomValue);
    return randomValue;
}

// Function to perform any necessary cleanup
void software_mrand48_fini()
{
    // No cleanup needed in this case
}
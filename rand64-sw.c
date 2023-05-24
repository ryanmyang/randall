#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "rand64-sw.h"


/* Input stream containing random bytes.  */
static FILE *urandstream;

/* Initialize the software rand64 implementation.  */
void
software_rand64_init(void)
{
    urandstream = fopen("/dev/random", "r");
    if (!urandstream)
        abort();
}

/* Return a random value, using software operations.  */
unsigned long long
software_rand64(void)
{

    unsigned long long int x;

    // if mrand48_r
    // x = mrand48_r()

    if (fread(&x, sizeof x, 1, urandstream) != 1)
        abort();


    return x;
}

/* Finalize the software rand64 implementation.  */
void
software_rand64_fini(void)
{
    fclose(urandstream);
}

void software_mrand48_init(void) {
    

}
unsigned long long software_mrand48(void) {
    unsigned long long int x;
    short int arr[3] = {1,2,3};
    struct drand48_data buffer;
    seed48_r(arr, &buffer);
    mrand48_r(&buffer, &x);
    return x;
}

void software_mrand48_fini(void) {

}
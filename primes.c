/*
 * primes.c: Generate a list of primes up to and including a given bound using
 * the Sieve of Atkin.
 *
 * Written by Joshua Morrison, 9-29-2017
 * Last Edited: 9-30-2017, 12:00am
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*** Type Declarations ***/
typedef unsigned long long int ulli;

#define FALSE (0)
#define TRUE (1)


// Integer Square Root
ulli isqrt(ulli x) {
    if (x < 2)
        return x;
    else {
        ulli sm = isqrt(x >> 2) << 1;
        ulli lg = sm + 1;
        
        if (lg*lg > x)
            return sm;
        else
            return lg;
    }
}

// Sieve of Atkin
int* sieve(ulli n) {
    int* data = calloc(n + 1, sizeof(int));
    data[2] = TRUE;
    data[3] = TRUE;
    
    ulli lim = isqrt(n);
    
    ulli x;
    for (x = 1; x <= lim; ++x) {
        ulli y;
        for (y = 1; y <= lim; ++y) {
            ulli k = (4*x*x) + (y*y);
            if ((k <= n) && ((k % 12 == 1) || (k % 12 == 5)))
                data[k] = !data[k];
            
            k = (3*x*x) + (y*y);
            if ((k <= n) && (k % 12 == 7))
                data[k] = !data[k];
            
            k = (3*x*x) - (y*y);
            if ((x > y) && (k <= n) && (k % 12 == 11))
                data[k] = !data[k];
        }
    }
    
    ulli j;
    for (j = 5; j <= lim; ++j) {
        if (data[j]) {
            for (ulli k = j*j; k <= n; k += j*j)
                data[k] = FALSE;
        }
    }
    
    return data;
}


int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Usage: primes [n]\n");
        printf("\tn: Bound for the sieve\n");
        exit(EXIT_FAILURE);
    }
    
    char* cend;
    ulli n = (ulli) strtoull(argv[1], &cend, 10);
    FILE* primes_file = fopen("primes.txt", "w");
    ulli count = 0;
    
    clock_t start = clock();
    int* is_prime = sieve(n);
    
    ulli k;
    for (k = 0; k <= n; ++k) {
        if (is_prime[k]) {
            fprintf(primes_file, "%llu\n", k);
            ++count;
        }
    }
    
    fclose(primes_file);
    clock_t end = clock();
    double time = (double) (end - start) / CLOCKS_PER_SEC;
    
    printf("%llu primes found below %llu in %.6f seconds\n", count, n, time);
}
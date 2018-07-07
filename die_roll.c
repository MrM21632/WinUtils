/*
 * die_roll.c: Die rolling utility. Generates a random number of the following
 * format: NdS(+/-)M.
 *     - N: number of dice being rolled.
 *     - S: number of sides per die; any number is allowed, and % can be used
 *          as a stand-in for 100.
 *     - M: modifier to apply to the roll (positive or negative).
 * This program also allows for multiple rolls (same format for all), if desired.
 *
 * Version:     1.0.0
 * License:     MIT License (see LICENSE.txt for more details)
 * Author:      Joshua Morrison (GitHub: MrM21632)
 * Last Edited: 7/4/2018, 1:45pm
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <pcg_variants.h>


int main(int argc, char **argv) {
    if (argc != 5) {
        printf("Usage: die_roll total dice sides mod\n");
        printf("Generates random numbers in the range [dice + mod, (dice)(sides) + mod].\n\n");
        printf("total\t\tTotal rolls to make (> 0)\n");
        printf("dice\t\tNumber of dice to roll (> 0)\n");
        printf("sides\t\tSides per die (any positive number, or %%)\n");
        printf("mod\t\tModifier to die roll (positive or negative)\n");

        return EXIT_FAILURE;
    }

    // Setting up the variables
    int total = atoi(argv[1]);
    int dice = atoi(argv[2]);
    int mod = atoi(argv[4]);

    int min = dice + mod;
    if (min <= 0)
        min = 1;  // Guaranteed minimum result

    int sides;
    if (argv[3][0] == '%')  // Percentile
        sides = 100;
    else
        sides = atoi(argv[3]);

    int max = (dice * sides) + mod;
    if (max <= 0)
        max = 1;  // Guaranteed maximum(?) result


    // Roll the bones
    pcg32_random_t rng;
    pcg32_srandom_r(&rng, time(NULL), (intptr_t)&rng);

    int i;
    for (i = 1; i <= total; ++i) {
        uint32_t result = pcg32_boundedrand_r(&rng, (max - min + 1)) + min;
        printf("Die Roll #%d: %u\n", i, result);
    }
}

/*
 * num_gen.c: Number generation utility. Generates a list of integers within a
 * given range (min to max).
 *
 * Version:     1.0.0
 * License:     MIT License (see LICENSE.txt for more details)
 * Author:      Joshua Morrison (GitHub: MrM21632)
 * Last Edited: 7/4/2018, 4:00pm
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <pcg_variants.h>


int main(int argc, char **argv) {
    if (argc != 4) {
        printf("Usage: num_gen total min max\n");
        printf("Generates a list of numbers in the range [min, max].\n\n");
        printf("total\t\tNumber of numbers to generate\n");
        printf("min\t\tMinimum bound for number generation\n");
        printf("max\t\tMaximum bound for number generation\n");

        return EXIT_FAILURE;
    }

    char *end;
    uint64_t total = (uint64_t) strtoull(argv[1], &end, 10);
    int32_t min = (int32_t) strtol(argv[2], &end, 10);
    int32_t max = (int32_t) strtol(argv[3], &end, 10);
    FILE *numbers_file = fopen("numbers.txt", "w");

    pcg32_random_t rng;
    pcg32_srandom_r(&rng, time(NULL), (intptr_t)&rng);

    uint64_t i;
    for (i = 0; i < total; ++i) {
        int32_t result = (int32_t)(pcg32_boundedrand_r(&rng, (max - min + 1))) + min;
        fprintf(numbers_file, "%ld\n", result);
    }

    fclose(numbers_file);
}

/*
 * tip.c: Tip Utility. Calculates total cost with tip, given a cost and tip
 * rate.
 *
 * Version:     1.0.0-rc1
 * License:     MIT License (see LICENSE.txt for more details)
 * Author:      Joshua Morrison (MrM21632)
 * Last Edited: 1/17/2018, 7:00pm
 */

#include <stdio.h>
#include <stdlib.h>


int main(int argc, char **argv) {
    if (argc != 3) {
        printf("Usage: tip cost rate\n");
        printf("\tcost: Initial cost before accounting for tips. (Format: ##.##)\n");
        printf("\trate: User-selected tip rate. (Format: ##.##)\n\n");
        printf("Calculates total cost with tip, given an initial cost and desired tip rate.\n");
        return EXIT_FAILURE;
    }
    
    double cost = atof(argv[1]);
    double rate = atof(argv[2]);
    double tip  = cost * rate;
    
    printf("Total cost, after tip: %.2f\n", cost + tip);
}
/*
 * tip.c: Tip Utility. Calculates total cost with tip, given a cost and tip
 * rate.
 *
 * Version:     1.0.0
 * License:     MIT License (see LICENSE.txt for more details)
 * Author:      Joshua Morrison (MrM21632)
 * Last Edited: 1/17/2018, 7:00pm
 */

#include <stdio.h>
#include <stdlib.h>


int main(int argc, char **argv) {
    if (argc != 3) {
        printf("Usage: tip cost rate\n");
        printf("Calculates total cost with tip, given a cost and tip rate.\n\n");
        printf("cost\t\tInitial cost before tips. Format: ##.##\n");
        printf("rate\t\tUser-selected tip rate. Format: ##.##\n");
        return EXIT_FAILURE;
    }
    
    double cost = atof(argv[1]);
    double rate = atof(argv[2]);
    double tip  = cost * rate;
    
    printf("Total cost, after tip: %.2f\n", cost + tip);
}

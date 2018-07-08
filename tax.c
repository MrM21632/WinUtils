/*
 * tax.c: Sales Tax Utility. Calculates a total amount owed given an initial
 * cost and a sales tax rate.
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
        printf("Usage: tax cost rate\n");
        printf("Calculates total amount owed after adding sales tax.\n\n");
        printf("cost\t\tInitial cost. Format: ##.##\n");
        printf("rate\t\tSales tax rate. Format: ##.##\n");
        return EXIT_FAILURE;
    }
    
    double cost = atof(argv[1]);
    double rate = atof(argv[2]);
    double tax = cost * rate;
    
    printf("Total cost: $%.2f\n", cost + tax);
}

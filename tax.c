/*
 * tax.c: Calculates total cost with sales tax, given a cost and tax
 *     rate.
 * 
 * Written by Joshua Morrison, 7-7-2017
 * Last Edited: 7-7-2017, 3:00pm
 */

#include <stdio.h>
#include <stdlib.h>


int main(int argc, char** argv) {
    if (argc != 3) {
        printf("Usage: tax [cost] [rate]\n");
        return EXIT_FAILURE;
    }
    
    // Relatively simple and straightforward: set the variables, calculate the
    // tax
    double cost = atof(argv[1]);
    double rate = atof(argv[2]);
    double tax = cost * rate;
    
    // Print the total cost
    printf("Total cost: $%.2f\n", cost + tax);
}
/*
 * change.c: Change-making program, given a cost and amount of money received.
 *
 * Written by Joshua Morrison, 7-10-2017
 * Last Edited: 7-10-2017, 9:30pm
 */

#include <stdio.h>
#include <stdlib.h>


int main(int argc, char** argv) {
    if (argc != 3) {
        printf("Usage: change [cost] [given]\n");
        printf("NOTE: Must enter values as integers (Ex: $10.00 as 1000)\n");
        return EXIT_FAILURE;
    }
    
    // Due to issues with type casting, this program opts to take in the
    // variables as integers, and to operate on them as integers only.
    int cost = atoi(argv[1]);
    int given = atoi(argv[2]);
    int left = cost - given;
    
    // Make a floating-point version of the amount left over, for outputting
    // purposes.
    int change = abs(left);
    double c = ((double) abs(left)) / 100.0;
    
    // Base cases:
    //     1. If there is not enough change, print a message alerting the user
    //        of this and exit.
    //     2. If there is exactly enough change, print a message alerting the
    //        user of this and exit.
    if (left > 0) {
        printf("You still owe $%.2f\n", c);
        return EXIT_SUCCESS;
    }
    if (left == 0) {
        printf("No change required.\n");
        return EXIT_SUCCESS;
    }
    
    // Dollar bills, quarters, dimes, nickels, pennies
    int b, q, d, n, p;
    b = change / 100;  // Get the total number of dollar bills
    q = (change % 100) / 25;  // Get the total number of quarters
    d = ((change % 100) % 25) / 10;  // Get the total number of dimes
    n = (((change % 100) % 25) % 10) / 5;  // Get the total number of nickels
    p = (((change % 100) % 25) % 10) % 5;  // Get the total number of pennies
    
    // Print the change by group
    printf("Return $%.2f, given as:\n", c);
    printf("\t%d dollars,\n", b);
    printf("\t%d quarters,\n", q);
    printf("\t%d dimes,\n", d);
    printf("\t%d nickels, and\n", n);
    printf("\t%d pennies.\n", p);
}
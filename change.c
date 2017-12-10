/*
 * change.c: Change Making Utility. Given a total cost and an amount of money
 * received, calculate and output the total change owed, broken down into the
 * most common American currency values.
 *
 * Version:     1.1.0
 * License:     MIT License (see LICENSE.txt for more details)
 * Author:      Joshua Morrison (MrM21632)
 * Last Edited: 12/09/2017, 8:27pm
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char** argv) {
    if (argc != 3) {
        printf("Usage: change cost given\n");
        printf("\tcost: Total cost. (Format: ##.##)\n");
        printf("\tgiven: Amount received. (Format: ##.##)\n\n");
        printf("Calculates change owed given a total cost and amount of money received.\n");
        printf("NOTE: Supports American currency only.\n");
        return EXIT_FAILURE;
    }
    
    double cost = atof(argv[1]);
    double given = atof(argv[2]);
    double diff = cost - given;
    
    if (diff > 0) {
        printf("You still owe $%.2f.\n", diff);
        return EXIT_SUCCESS;
    }
    if (diff == 0) {
        printf("Exact amount given; no change required.\n");
        return EXIT_SUCCESS;
    }
    
    // The conversion algorithm below is designed to avoid any issues with type
    // conversions. Any variation will cause the program to not function
    // properly.
    diff = fabs(diff);
    int diff_as_int = (int) floor((diff * 100.0) + 0.5);
    
    int b = diff_as_int / 100;                      // Dollar Bills
    int q = (diff_as_int % 100) / 25;               // Quarters
    int d = ((diff_as_int % 100) % 25) / 10;        // Dimes
    int n = (((diff_as_int % 100) % 25) % 10) / 5;  // Nickels
    int p = (((diff_as_int % 100) % 25) % 10) % 5;  // Pennies
    
    printf("$%.2f extra given. Return the following:\n", diff);
    printf("\t%d dollar bill(s),\n", b);
    printf("\t%d quarter(s),\n", q);
    printf("\t%d dime(s),\n", d);
    printf("\t%d nickel(s), and\n", n);
    printf("\t%d penny(ies).\n", p);
}
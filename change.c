/*
 * change.c: Change Making Utility. Given a total cost and an amount of money
 * received, calculate and output the total change owed, broken down into the
 * most common American currency values.
 *
 * Version:     1.0.0-rc1
 * License:     MIT License (see LICENSE.txt for more details)
 * Author:      Joshua Morrison (MrM21632)
 * Last Edited: 1/17/2018, 7:00pm
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char **argv) {
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
    // 
    // At this point, diff is negative, so we need to make it positive first.
    // Next, we convert diff to the total number of cents (whole number).
    //     1. We multiply diff by 100, making it equivalent to the number of
    //        pennies left over.
    //     2. We add 0.5 to account for the truncation that occurs when computing
    //        floor(). Not doing this can cause the program to lose information,
    //        which will make the remaining calculations incorrect.
    //     3. Take the floor of the calculation, then convert it to an integer.
    diff = fabs(diff);
    int cents = (int) floor((diff * 100.0) + 0.5);
    
    int b = cents / 100;                      // Dollar Bills
    int q = (cents % 100) / 25;               // Quarters
    int d = ((cents % 100) % 25) / 10;        // Dimes
    int n = (((cents % 100) % 25) % 10) / 5;  // Nickels
    int p = (((cents % 100) % 25) % 10) % 5;  // Pennies
    
    printf("$%.2f extra given. Return the following:\n", diff);
    printf("\t%d dollar bill(s),\n", b);
    printf("\t%d quarter(s),\n", q);
    printf("\t%d dime(s),\n", d);
    printf("\t%d nickel(s), and\n", n);
    printf("\t%d penny(ies).\n", p);
}
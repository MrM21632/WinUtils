/*
 * const.c: Numerical Constant Utility. Prints a specified mathematical/physical
 * constant to a given precision. Currently, the following constants are
 * supported:
 *     - Apery's Constant, or Zeta(3) (apery)
 *     - Archimedes' Constant (pi)
 *     - Euler's/Napier's Number (e)
 *     - The Euler-Mascheroni Constant (masch)
 *     - The Golden Ratio (ratio)
 *     - Square Root of 2 (root2)
 *     - Square Root of 3 (root3)
 *
 * Version:     1.1.0
 * License:     MIT License (see LICENSE.txt for more details)
 * Author:      Joshua Morrison (MrM21632)
 * Last Edited: 12/09/2017, 8:30pm
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char** argv) {
    if (argc != 3) {
        printf("Usage: const num prec\n");
        printf("\tnum: The desired constant. Choose one of the following:\n");
        printf("\t\tapery: Apery's Constant, also known as Zeta(3)\n");
        printf("\t\te: Euler's Number\n");
        printf("\t\tmasch: Euler-Mascheroni Constant\n");
        printf("\t\tpi: Archimedes' Constant\n");
        printf("\t\tratio: The Golden Ratio\n");
        printf("\t\troot2: Square Root of 2\n");
        printf("\t\troot3: Square Root of 3\n");
        printf("\tprec: The desired point of precision (Max 1 billion)\n\n");
        printf("Print a numeric constant to the specified precision.\n");
        return EXIT_FAILURE;
    }
    
    const char* c = (const char*) argv[1];
    const char* d = ".\\data\\";
    const char* s = "_digits.txt";
    int p = atoi(argv[2]);
    
    // Construct the filename, then open the file (read-only)
    char file[26];
    strcpy(file, d);
    strcat(file, c);
    strcat(file, s);
    FILE* const_file = fopen((const char*) file, "r");
    
    // Output the constant to the desired precision, then exit
    int i = 0, ch;
    while (((ch = fgetc(const_file)) != EOF) && i < p + 2) {
        putchar(ch);
        ++i;
    }
    
    fclose(const_file);  // Close the file once we're done!
}
/*
 * const.c: Utility that prints a specified mathematical constant up to one
 *     billion points of precision. Currently, the following constants are
 *     supported:
 *     - Apery's Constant, or Zeta(3) (apery)
 *     - Archimedes' Constant (pi)
 *     - Euler's Number (e)
 *     - The Euler-Mascheroni Constant (masch)
 *     - The Golden Ratio (ratio)
 *
 * Written by Joshua Morrison, 9-15-2017
 * Last Edited: 9-15-2017, 8:00pm
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*** Type Declarations ***/
typedef unsigned long long int ulli;


int main(int argc, char** argv) {
    if (argc != 3) {
        printf("Usage: const [const] [prec]\n");
        printf("\tconst: The desired constant. The following are supported\n");
        printf("\t\tapery: Apery's Constant, or Zeta(3)\n");
        printf("\t\te: Euler's Number\n");
        printf("\t\tmasch: Euler-Mascheroni Constant\n");
        printf("\t\tpi: Archimedes' Constant\n");
        printf("\t\tratio: The Golden Ratio\n");
        printf("\tprec: The desired point of precision\n");
        return EXIT_FAILURE;
    }
    
    const char* c = (const char*) argv[1];
    const char* d = ".\\data\\";
    const char* s = "_digits.txt";
    ulli p = (ulli) atoi(argv[2]);
    
    // Make the filename, then open the file
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
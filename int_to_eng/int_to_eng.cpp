/*
 * int_to_eng.cpp: Number-to-English Utility. Given an integer in the range
 * [-2^63, 2^63), output the number in correct English notation.
 *
 * Version:     1.0.0
 * License:     Public Domain
 * Author:      Joshua Morrison (jmorrison708@comcast.net)
 * Last Edited: 10/28/2017, 8:00pm
 */

#include <iostream>
#include <string>
#include <cstdlib>

typedef long long int lli;

/* Arrays containing constant string values for numbers */
std::string tens[10] = { "", "", "twenty ", "thirty ", "forty ", "fifty ", "sixty ", "seventy ", "eighty ", "ninety " };
std::string tens_special[10] = { "ten ", "eleven ", "twelve ", "thirteen ", "fourteen ", "fifteen ", "sixteen ", "seventeen ", "eighteen ", "nineteen " };
std::string ones[10] = { "zero", "one ", "two ", "three ", "four ", "five ", "six ", "seven ", "eight ", "nine " };


/**
 * abs(): Calculate the absolute value of n.
 *
 * Input:  lli n - the number to perform the operation on.
 * Output: |n|.
 */
lli ll_abs(lli n) {
    lli mask = n >> ((sizeof(lli) * CHAR_BIT) - 1);
    return (n + mask) ^ mask;
}

/**
 * to_english(): Converts the given number to its proper English equivalent.
 *
 * Input:  lli n - the number in question.
 * Output: The English equivalent of n.
 */
std::string to_english(lli n) {
    // Setup the string to be returned. If the number is negative, set the string
    // up to accomomodate that, and let n = |n|.
    std::string n_str = "";
    
    if (n < 0) {
        n_str += "negative ";
        n = ll_abs(n);
    }
    
    // Recursively generate the string through use of division and modulus, then
    // return it. Note that, at this point, n is positive.
    if (n < 10)
        n_str += ones[n];
    else if (n >= 10 && n < 20)
        n_str += tens_special[n - 10];
    else if (n >= 20 && n < 100)
        n_str += tens[n / 10] + (n % 10 == 0 ? "" : ones[n % 10]);
    else if (n >= 100 && n < 1000)
        n_str += ones[n / 100] + "hundred" + (n % 100 == 0 ? "" : " " + to_english(n % 100));
    else if (n >= 1000 && n < 1000000)
        n_str += to_english(n / 1000) + "thousand" + (n % 1000 == 0 ? "" : ", " + to_english(n % 1000));
    else if (n >= 1000000 && n < 1000000000)
        n_str += to_english(n / 1000000) + "million" + (n % 1000000 == 0 ? "" : ", " + to_english(n % 1000000));
    else if (n >= 1000000000 && n < 1000000000000LL)
        n_str += to_english(n / 1000000000) + "billion" + (n % 1000000000 == 0 ? "" : ", " + to_english(n % 1000000000));
    else if (n >= 1000000000000LL && n < 1000000000000000LL)
        n_str += to_english(n / 1000000000000LL) + "trillion" + (n % 1000000000000LL == 0 ? "" : ", " + to_english(n % 1000000000000LL));
    else if (n >= 1000000000000000LL && n < 1000000000000000000LL)
        n_str += to_english(n / 1000000000000000LL) + "quadrillion" + (n % 1000000000000000LL == 0 ? "" : ", " + to_english(n % 1000000000000000LL));
    else if (n >= 1000000000000000000LL)
        n_str += to_english(n / 1000000000000000000LL) + "quintillion" + (n % 1000000000000000000LL == 0 ? "" : ", " + to_english(n % 1000000000000000000LL));
    
    return n_str;
}


int main(int argc, char** argv) {
    if (argc != 2) {
        std::cout << "Usage: int_to_eng [num]\n";
        std::cout << "\tnum: Number to convert to English, in the range (-(2^63), 2^63)\n";
        return EXIT_FAILURE;
    }
    
    char *e;
    lli num = std::strtoll(argv[1], &e, 10);
    std::string num_str = to_english(num);
    
    std::cout << num << ": " << num_str << "\n";
}
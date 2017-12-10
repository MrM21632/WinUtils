/*
 * sort.cpp: Sorting Utility. Given a list of numbers (via a file), sort them in
 * ascending order with a considerably fast sorting algorithm. For purposes of
 * speed, we will be using Quicksort.
 *
 * Version:     1.1.0
 * License:     MIT License (see LICENSE.txt for more details)
 * Author:      Joshua Morrison (MrM21632)
 * Last Edited: 12/09/2017, 11:05pm
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>


typedef long long int lli;

/**
 * swap(): XOR-Swap algorithm, defined for long long int.
 *
 * Input:  lli *x, *y - the values to swap. It is required that they are not the
 *             exact same value (i.e., they don't have the same memory address).
 * Output: N/A, because the values are swapped in-place.
 */
void swap(lli* x, lli* y) {
    if (x != y) {
        *x ^= *y;
        *y ^= *x;
        *x ^= *y;
    }
}

/**
 * quicksort(): In-place Quicksort algorithm for vectors. Sorts a vector of
 * elements in ascending order.
 *
 * Input:  std::vector<lli> &v - reference of vector to be sorted.
 *         int lo - lower bound for sorting.
 *         int hi - upper bound for sorting.
 * Output: N/A. Since the vector is sorted in-place, nothing needs to be
 *         returned.
 */
void quicksort(std::vector<lli>& v, int lo, int hi) {
    if (lo < hi) {
        lli pivot = v[(lo + hi) / 2];
        int left = lo, right = hi;

        while (left <= right) {
            while (v[left] < pivot)
                ++left;
            while (v[right] > pivot)
                --right;
            if (left <= right) {
                swap(&v[left], &v[right]);
                ++left;
                --right;
            }
        }

        quicksort(v, lo, right);
        quicksort(v, left, hi);
    }
}


int main(int argc, char** argv) {
    if (argc != 2) {
        std::cout << "Usage: sort file" << std::endl;
        std::cout << "\tfile: File containing numbers to sort (Integers only).\n\n";
        std::cout << "Sorts a list of integers and outputs the sorted list to a file.\n";
        return EXIT_FAILURE;
    }
    
    clock_t start = std::clock();
    
    std::vector<lli> data;
    std::ifstream fin(argv[1]);
    std::ofstream fout("sorted.txt");
    
    std::string s;
    while (std::getline(fin, s)) {
        lli x = static_cast<lli>(std::stoll(s));
        data.push_back(x);
    }
    
    quicksort(data, 0, data.size() - 1);
    
    for (std::vector<lli>::iterator vit = data.begin(); vit != data.end(); ++vit)
        fout << *vit << "\n";
    
    clock_t end = std::clock();
    double time = static_cast<double>(end - start) / CLOCKS_PER_SEC;
    
    std::cout << "Elapsed Time: " << time << " seconds.\n";
}
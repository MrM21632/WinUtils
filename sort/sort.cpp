/*
 * sort.cpp: Sorting Utility. Given a list of numbers (via a file), sort them in
 * ascending order with a considerably fast sorting algorithm. For purposes of
 * speed, we will be using Quicksort.
 *
 * Version:     1.0.0
 * License:     MIT License (see LICENSE.txt for more details)
 * Author:      Joshua Morrison (MrM21632)
 * Last Edited: 1/17/2018, 5:00pm
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdint>
#include <cstdlib>
#include <ctime>


/**
 *  @brief XOR Swap
 *  
 *  @param [in] x Operand
 *  @param [in] y Operand
 *  @return N/A.
 *  
 *  @details Swaps two integers in-place using XOR operations.
 */
void swap(int64_t *x, int64_t *y) {
    if (x != y) {
        *x ^= *y;
        *y ^= *x;
        *x ^= *y;
    }
}

/**
 *  @brief Quicksort
 *  
 *  @param [in] v  Reference to container to be sorted
 *  @param [in] lo Lower bound for sorting
 *  @param [in] hi Upper bound for sorting
 *  @return N/A.
 *  
 *  @details Performs quicksort in-place on a vector, sorting its contents. Uses
 *           XOR swap to swap the vector's contents.
 */
void quicksort(std::vector<int64_t> &v, int lo, int hi) {
    if (lo < hi) {
        int64_t pivot = v[(lo + hi) / 2];
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


int main(int argc, char **argv) {
    if (argc != 2) {
        std::cout << "Usage: sort file" << std::endl;
        std::cout << "\tfile: File containing numbers to sort (Integers only).\n\n";
        std::cout << "Sorts a list of integers and outputs the sorted list to a file.\n";
        return EXIT_FAILURE;
    }
    
    clock_t start = std::clock();
    
    std::vector<int64_t> data;
    std::ifstream fin(argv[1]);
    std::ofstream fout("sorted.txt");
    
    std::string s;
    while (std::getline(fin, s)) {
        int64_t x = static_cast<int64_t>(std::stoll(s));
        data.push_back(x);
    }
    fin.close();
    
    quicksort(data, 0, data.size() - 1);
    
    for (std::vector<int64_t>::iterator it = data.begin(); it != data.end(); ++it)
        fout << *it << "\n";
    fout.close();
    
    clock_t end = std::clock();
    double time = static_cast<double>(end - start) / CLOCKS_PER_SEC;
    
    std::cout << "Process Completed. Elapsed Time: " << time << " seconds.\n";
}
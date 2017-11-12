/*
 * sort.cpp: Sorting Utility. Given a list of numbers (via a file), sort them in
 * ascending order with a considerably fast sorting algorithm. For purposes of
 * generalization and applicability, we will be using Merge Sort.
 *
 * Written by Joshua Morrison, 9-29-2017
 * Last Edited: 9-29-2017, 11:00pm
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

/*** Function and Type Declarations ***/
typedef long long int lli;
void swap(lli*, lli*);
void quicksort(std::vector<lli>&, int, int);


int main(int argc, char** argv) {
    if (argc != 2) {
        std::cout << "Usage: sort [file]" << std::endl;
        std::cout << "\tfile: File containing numbers to sort (Integers only)" << std::endl;
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
        fout << *vit << std::endl;
    
    clock_t end = std::clock();
    double time = static_cast<double>(end - start) / CLOCKS_PER_SEC;
    
    std::cout << "Elapsed Time: " << time << " seconds" << std::endl;
}


/*** Function Definitions ***/

// XOR-Swap
void swap(lli* x, lli* y) {
    if (x != y) {
        *x ^= *y;
        *y ^= *x;
        *x ^= *y;
    }
}

// Quicksort
void quicksort(std::vector<lli>& a, int lo, int hi) {
    if (lo < hi) {
		lli pivot = a[(lo + hi) / 2];
		int left = lo, right = hi;

		while (left <= right) {
			while (a[left] < pivot)
				++left;
			while (a[right] > pivot)
				--right;
			if (left <= right) {
				swap(&a[left], &a[right]);
				++left;
				--right;
			}
		}

		quicksort(a, lo, right);
		quicksort(a, left, hi);
    }
}
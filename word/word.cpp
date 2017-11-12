/*
 * word.cpp: Reads in a file of words, then prints a random word.
 *
 * Written by Joshua Morrison, 2-24-2017
 * Personal Project
 * Last Edited: 5-10-2017, 11:00pm
 */

#include <iostream>
#include <fstream>
#include <random>
#include <string>
#include <vector>
#include <locale>
#include <codecvt>
#include <cstdlib>
#include <ctime>
#include <fcntl.h>
#include <io.h>
#include <wchar.h>
#include <windows.h>

/*** Function Declarations ***/
std::vector<std::wstring> read_file(const wchar_t*);
std::wstring get_line(const std::vector<std::wstring>&);


int wmain(int argc, wchar_t* argv[]) {
    if (argc != 2) {
        std::wcout << L"Usage: word [lang]" << std::endl;
        std::wcout << L"\tlang: Choose from de,en,es,fr,gr,it,la,pt,ru,sv" << std::endl;
        return EXIT_FAILURE;
    }
    
    // We'll time this for diagnostic purposes, as well as for the sake of knowing
    clock_t start = std::clock();
    
    // Specify the program will be outputting to cmd in UTF-16
    _setmode(_fileno(stdout), _O_U16TEXT);
    
    // Prep the filename for usage
	const wchar_t* arg = argv[1];
	std::wstring filename(L".\\data\\words_");
	filename += std::wstring(arg) + std::wstring(L".txt");
	const wchar_t* f = filename.c_str();
    
    // Read the file and obtain the word
	std::vector<std::wstring> data = read_file(f);
    std::wstring line = get_line(data);
    
    clock_t end = std::clock();
    double time = static_cast<double>(end - start) / CLOCKS_PER_SEC;
    
    std::wcout << line << std::endl;
    std::wcout << "Obtained in " << time << " seconds." << std::endl;
}


/*** Function Definitions ***/

// Read the given file
std::vector<std::wstring> read_file(const wchar_t* file) {
    // Open the file, also declare other necessary variables
	std::vector<std::wstring> data;
    std::wifstream fin;
    std::wstring line;
    fin.open(file);
    
    fin.imbue(std::locale(fin.getloc(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::consume_header>));
    while (std::getline(fin, line))
        data.push_back(line);
    
    return data;
}

// Return random line from string
std::wstring get_line(const std::vector<std::wstring>& data) {
    int size = data.size();
    
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(0, size - 1);
    
    return data[dist(mt)];
}
/*
 * word.cpp: Word Utility. Randomly prints out a word from a list of words from
 * a specified language.
 *
 * Version:     1.2.0
 * License:     MIT License (see LICENSE.txt for more details)
 * Author:      Joshua Morrison (MrM21632)
 * Last Edited: 12/09/2017, 11:35pm
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


/**
 * read_file(): Reads the contents of a file. Supports Unicode text.
 * 
 * Input:  const wchar_t* file - the name of the file to read in.
 * Output: A vector of the file's lines.
 */
std::vector<std::wstring> read_file(const wchar_t* file) {
    std::vector<std::wstring> data;
    std::wifstream fin;
    std::wstring line;
    fin.open(file);
    
    fin.imbue(std::locale(fin.getloc(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::consume_header>));
    while (std::getline(fin, line))
        data.push_back(line);
    
    return data;
}

/**
 * get_line(): Randomly selects a string from a vector of strings.
 * 
 * Input:  const std::vector<std::wstring>& data - Reference to the vector.
 * Output: A randomly selected string from the vector.
 */
std::wstring get_line(const std::vector<std::wstring>& data) {
    int size = data.size();
    
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(0, size - 1);
    
    return data[dist(mt)];
}


int wmain(int argc, wchar_t* argv[]) {
    if (argc != 2) {
        std::wcout << L"Usage: word lang\n";
        std::wcout << L"\tlang: Choose from de,en,es,fr,gr,it,la,pt,ru,sv\n\n";
        std::wcout << "Outputs a randomly selected word from a specified list.\n";
        return EXIT_FAILURE;
    }
    
    // We'll time this for diagnostic purposes, as well as for the sake of
    // knowing how long it takes on average.
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
    std::wcout << "Obtained in " << time << " seconds.\n";
}
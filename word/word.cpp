/*
 * word.cpp: Word Utility. Randomly prints out a word from a list of words from
 * a specified language.
 * This program has been heavily specialized to work in Windows' Command Prompt.
 * If you plan to use this on a different platform, you will need to make
 * extensive changes to this code for it to work correctly.
 *
 * Version:     1.0.0
 * License:     MIT License (see LICENSE.txt for more details)
 * Author:      Joshua Morrison (MrM21632)
 * Last Edited: 1/17/2018, 5:00pm
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
 *  @brief Read a File's Contents to a Vector
 *  
 *  @param [in] file File to be read
 *  @return A vector containing all words in the file.
 *  
 *  @details Reads the file line-by-line (each line should be a single word) and
 *           enters them into a vector.
 */
std::vector<std::wstring> read_file(const wchar_t *file) {
    std::vector<std::wstring> data;
    std::wifstream fin;
    std::wstring line;
    fin.open(file);

    fin.imbue(std::locale(fin.getloc(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::consume_header>));
    while (std::getline(fin, line))
        data.push_back(line);
    fin.close();

    return data;
}

/**
 *  @brief Randomly Select a String
 *  
 *  @param [in] data Reference of vector to choose string from
 *  @return A randomly-chosen string from the vector.
 *  
 *  @details Randomly chooses a string from the given vector.
 */
std::wstring get_line(const std::vector<std::wstring> &data) {
    int size = data.size();

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(0, size - 1);

    return data[dist(mt)];
}


int wmain(int argc, wchar_t **argv) {
    if (argc != 2) {
        std::wcout << L"Usage: word lang\n";
        std::wcout << L"\tlang: Choose from de,en,es,fr,gr,it,la,pt,ru,sv\n\n";
        std::wcout << L"Outputs a randomly selected word from a specified list.\n";
        return EXIT_FAILURE;
    }

    // We'll time this for diagnostic purposes, as well as for the sake of
    // knowing how long it takes on average.
    clock_t start = std::clock();

    // Specify the program will be outputting to cmd in UTF-16
    _setmode(_fileno(stdout), _O_U16TEXT);

    // Prep the filename for usage
    const wchar_t *arg = argv[1];
    std::wstring filename(L".\\data\\dict\\");
    filename += std::wstring(arg) + std::wstring(L".dict");
    const wchar_t *f = filename.c_str();

    // Read the file and obtain the word
    std::vector<std::wstring> data = read_file(f);
    std::wstring line = get_line(data);

    clock_t end = std::clock();
    double time = static_cast<double>(end - start) / CLOCKS_PER_SEC;

    std::wcout << line << std::endl;
    std::wcout << L"Obtained in " << time << L" seconds.\n";
}

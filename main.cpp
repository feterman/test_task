#include <algorithm>
#include <iostream>

#include "functions.hpp"

// местами дурацкий имена переменных, но решил, что в рамках тестового задания это нормально
int main(int argc, const char** argv)
{
    if (argc != 4) { 
        std::cout << "The program requires 3 parameters: file path to read, write and string to delete\n";
        return 0;
    }
    std::string file_str;
    if (auto res = readFile(argv[1]); !res) {
        std::cout << "Reading file not found\n";
        return 0;
    }
    else {
        file_str = res.value();
    }
    auto strs = split(file_str);
    std::string word{ argv[2] };
    for (auto& str : strs) {
        deleteWord(str, word);
    }
    std::sort(strs.begin(), strs.end(), compareString);
    saveResult(argv[3], strs);
}
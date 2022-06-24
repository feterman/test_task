#include <fstream>
#include <iostream>

#include "functions.hpp"

std::optional<std::string> readFile(const std::filesystem::path& path)
{
    if (!std::filesystem::exists(path)) {
        return {};
    }
    std::ifstream file(path, std::ifstream::binary);
    file.seekg(0, std::ios::end);
    size_t size = file.tellg();
    std::string buffer(size, ' ');
    file.seekg(0);
    file.read(&buffer[0], size);
    return buffer;
}

std::vector<std::string> split(std::string str)
{
    std::vector<std::string> strs;
    auto pos = str.find('\n');
    if (!str.empty() && (pos == std::string::npos)) {
        strs.push_back(str);
    }
    while (pos != std::string::npos) {
        strs.push_back(str.substr(0, pos));
        str.erase(0, pos + 1);
        pos = str.find('\n');
    }
    return strs;
}

bool compareString(const std::string& str1, const std::string& str2)
{
    if (str1.size() < str2.size()) {
        return true;
    }
    else if (str1.size() > str2.size()) {
        return false;
    }
    for (std::size_t i = 0; i < str1.size(); i++) {
        if (std::tolower(str1[i]) < std::tolower(str2[i])) {
            return true;
        }
        else if (std::tolower(str1[i]) > std::tolower(str2[i])) {
            return false;
        }
    }
    return false;
}

void deleteWord(std::string& str, const std::string& word)
{
    if(word.empty()){
        return;
    }
    auto pos = str.find(word);
    while (pos != std::string::npos) {
        str.erase(pos, word.size());
        pos = str.find(word);
    }
}

void saveResult(const std::filesystem::path& path, const std::vector<std::string>& strs)
{
    std::ofstream of{ path };
    if (!of.is_open()) {
        std::cout << "Error when opening a file for writing\n";
        return;
    }
    for (auto& str : strs) {
        of << str << std::endl;
    }
}
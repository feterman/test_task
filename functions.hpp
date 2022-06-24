#pragma once

#include <filesystem>
#include <optional>
#include <string>
#include <vector>


std::optional<std::string> readFile(const std::filesystem::path& path);

std::vector<std::string> split(std::string str);

bool compareString(const std::string& str1, const std::string& str2);

void deleteWord(std::string& str, const std::string& word);

void saveResult(const std::filesystem::path& path, const std::vector<std::string>& strs);
//
// Created by Daniil Bakushkin on 19.03.2024.
//
#pragma once
#ifndef SHAD_CPP0_UTILS_H
#define SHAD_CPP0_UTILS_H

#endif  // SHAD_CPP0_UTILS_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <filesystem>

std::string ReadTextFromFile(const std::filesystem::path& path) {
    std::ifstream t(path);
    if (!t.is_open()) {
        throw std::runtime_error("Unable to open the file");
    }
    std::stringstream buffer;
    buffer << t.rdbuf();
    return buffer.str();
}

void WriteTextToFile(const std::filesystem::path& path, const std::string& text) {
    std::ofstream out(path);

    if (!out.is_open()) {
        throw std::runtime_error("Unable to open the file");
    }
    out << text;
    out.close();
}

template <class T1, class T2>
void PrintOutMap(const std::map<T1, T2>& map_chars) {
    for (const auto& [key, value] : map_chars) {
        std::cout << key << ':' << value << ' ';
    }
}
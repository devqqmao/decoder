//
// Created by Daniil Bakushkin on 19.03.2024.
//

#ifndef SHAD_CPP0_LOAD_GRAMS_H
#define SHAD_CPP0_LOAD_GRAMS_H

#endif  // SHAD_CPP0_LOAD_GRAMS_H
#pragma once

struct Holder {
    std::map<std::string, double> map_grams;
    std::map<char, char> map_chars;
    double sum;
};

std::string StrTolower(std::string s) {
    std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c) { return std::tolower(c); });
    return s;
}

void ReadGramsFromFile(const std::filesystem::path& path, Holder& holder) {
    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open the file");
    }

    std::string key;
    double value;
    double sum = 0;

    while (file >> key >> value) {
        holder.map_grams[StrTolower(key)] = value;
        sum += value;
    }
    file.close();
    holder.sum = sum;
}

void CalculateLogProbs(Holder& holder) {
    for (auto& [key, value] : holder.map_grams) {
        holder.map_grams[key] = log((value + 1) / holder.sum);
    }
}

void CollectCharsDict(Holder& holder) {
    char ch = 'a';
    while (ch <= 'z') {
        holder.map_chars[ch] = ch;
        ++ch;
    }
}

Holder CollectHolder(const std::filesystem::path& path) {

    std::map<std::string, double> map_grams{};
    std::map<char, char> map_chars{};
    auto holder = Holder{map_grams, map_chars, 0};

    ReadGramsFromFile(path, holder);
    CalculateLogProbs(holder);
    CollectCharsDict(holder);
    return holder;
}
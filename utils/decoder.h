//
// Created by Daniil Bakushkin on 19.03.2024.
//

#ifndef SHAD_CPP0_DECODER_H
#define SHAD_CPP0_DECODER_H

#endif  // SHAD_CPP0_DECODER_H

#include <random>
#pragma once

using std::cout;
using std::endl;

std::string TrimText(const std::string& text) {
    std::stringstream ss;
    for (int i = 0; i < text.size(); ++i) {
        if (isalpha(text[i])) {
            ss << static_cast<char>(tolower(text[i]));
        }
    }
    return ss.str();
}
double EvaluatePermutation(const std::string& trimmed_text,
                           const std::map<std::string, double>& map_grams,
                           const std::map<char, char>& map_chars, double dflt) {
    double sum_log_prob = 0;
    int q_gram = 4;
    int s = static_cast<int>(trimmed_text.size());
    if (s < q_gram) {
        return 0;
    }
    int k;
    std::stringstream ss;
    for (int i = 0; i < s - (q_gram - 1); ++i) {
        ss.str("");
        for (k = 0; k < q_gram; ++k) {
            ss << map_chars.at(trimmed_text[i + k]);
        }
        if (map_grams.find(ss.str()) != map_grams.end()) {
            sum_log_prob += map_grams.at(ss.str());
        } else {
            sum_log_prob += dflt;
        }
    }
    return sum_log_prob;
}

std::pair<char, char> PermutateMap(std::map<char, char>& map_chars, std::mt19937* gen) {
    std::uniform_int_distribution<int> dist(0, map_chars.size() - 1);
    char ch0 = dist(*gen) + 'a';
    char ch1 = dist(*gen) + 'a';
    char res0 = map_chars.at(ch0);
    char res1 = map_chars.at(ch1);
    map_chars[ch0] = res1;
    map_chars[ch1] = res0;
    return std::make_pair(ch0, ch1);
}

void PermutateMapBWD(std::map<char, char>& map_chars, std::pair<char, char> pr) {
    char res0 = map_chars.at(pr.first);
    char res1 = map_chars.at(pr.second);
    map_chars[pr.first] = res1;
    map_chars[pr.second] = res0;
}

std::string Decode(const std::string& text, const std::map<char, char>& map_chars);

void LoggerInfo(int i, const std::map<char, char>& curr_map, const std::map<char, char>& test_map,
                double curr_metric, const std::string& text) {
    cout << "iter: " << i << endl;
    cout << "curr_map: ";
    PrintOutMap(curr_map);
    cout << endl;
    cout << "test_map: ";
    PrintOutMap(test_map);
    cout << endl;
    cout << "curr_metric: " << curr_metric << endl;
    cout << "text: " << text << endl;
    cout << "decoded text: " << Decode(text, curr_map) << endl;
}

template <class T1, class T2>
void CopyMap(const std::map<T1, T2>& src, std::map<T1, T2>& dst) {
    dst.clear();
    dst.insert(src.begin(), src.end());
}

std::map<char, char> FindPermutation(const std::string& text, const Holder& holder) {
    std::string trimmed_text = TrimText(text);
    int n_iters = 2'000;
    int seed = 42;
    std::mt19937 gen(seed);

    std::map<char, char> curr_map{};
    std::map<char, char> test_map{};
    CopyMap(holder.map_chars, curr_map);
    CopyMap(holder.map_chars, test_map);

    double curr_metric = 0;
    double test_metric;
    double dflt = log(1 / holder.sum);
    std::pair<char, char> pr;

    for (int i = 0; i < n_iters; ++i) {
        if (i % 100 == 0) {
            LoggerInfo(i, curr_map, test_map, curr_metric, text.substr(0, 16));
        }

        pr = PermutateMap(test_map, &gen);
        curr_metric = EvaluatePermutation(trimmed_text, holder.map_grams, curr_map, dflt);
        test_metric = EvaluatePermutation(trimmed_text, holder.map_grams, test_map, dflt);
        if (test_metric > curr_metric) {
            CopyMap(test_map, curr_map);
        } else {
            PermutateMapBWD(test_map, pr);
        }
    }
    return curr_map;
}

std::string Decode(const std::string& text, const std::map<char, char>& map_chars) {
    std::stringstream ss;
    ss.clear();
    ss.str("");
    char c;
    bool up;
    for (int i = 0; i < text.size(); ++i) {
        c = text[i];
        up = false;
        if (isalpha(c)) {
            if (isupper(c)) {
                up = true;
            }
            c = std::tolower(c);
            c = map_chars.at(c);
            if (up) {
                c = toupper(c);
            }
        }
        ss << c;
    }
    return ss.str();
}

void Solve() {
    std::filesystem::path path;
    path =
        "/Users/dev.daniil.bakushkin/Desktop/shad/cpp-1/public-2023-fall/decoder-attempt/tests/"
        "second.txt";
    std::string text = ReadTextFromFile(path);

    path =
        "/Users/dev.daniil.bakushkin/Desktop/shad/cpp-1/public-2023-fall/decoder-attempt/"
        "english_quadgrams.txt";
    auto holder = CollectHolder(path);

    auto map_decode = FindPermutation(text, holder);
    std::string decoded_text = Decode(text, map_decode);
    path =
        "/Users/dev.daniil.bakushkin/Desktop/shad/cpp-1/public-2023-fall/decoder-attempt/tests/"
        "second_decoded.txt";
    WriteTextToFile(path, decoded_text);
}
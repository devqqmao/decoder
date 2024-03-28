//
// Created by Daniil Bakushkin on 19.03.2024.
//

#ifndef SHAD_CPP0_TESTS_H
#define SHAD_CPP0_TESTS_H

#pragma once

#endif  // SHAD_CPP0_TESTS_H
#include "utils.h"
#include "load_grams.h"
#include <set>

void TestReadWriteFile() {
    std::filesystem::path path;
    path =
        "/Users/dev.daniil.bakushkin/Desktop/shad/cpp-1/public-2023-fall/decoder-attempt/"
        "func_tests/"
        "romeo_and_juliet_r.txt";

    std::string content = ReadTextFromFile(path);
    path =
        "/Users/dev.daniil.bakushkin/Desktop/shad/cpp-1/public-2023-fall/decoder-attempt/"
        "func_tests/"
        "romeo_and_juliet_w.txt";
    WriteTextToFile(path, content);
}

void TestGrams() {
    std::filesystem::path path;
    path =
        "/Users/dev.daniil.bakushkin/Desktop/shad/cpp-1/public-2023-fall/decoder-attempt/"
        "func_tests/"
        "english_quadgrams_small.txt";

    std::map<std::string, double> map_grams{};
    std::map<char, char> map_chars{};
    auto holder = Holder{map_grams, map_chars, 0};

    ReadGramsFromFile(path, holder);

    cout << "Load pure numbers:" << endl;
    PrintOutMap(holder.map_grams);
    cout << endl;

    cout << "Show sum:" << endl;
    cout << holder.sum;
    cout << endl;

    CalculateLogProbs(holder);
    cout << "Calculate log probs: " << endl;
    PrintOutMap(holder.map_grams);
    cout << endl;

    CollectCharsDict(holder);
    cout << "Add chars: " << endl;
    PrintOutMap(holder.map_chars);
    cout << endl;
}

void TestEvaluatePermutation() {
    std::filesystem::path path =
        "/Users/dev.daniil.bakushkin/Desktop/shad/cpp-1/public-2023-fall/decoder-attempt/"
        "english_quadgrams.txt";
    //    std::filesystem::path path =
    //        "/Users/dev.daniil.bakushkin/Desktop/shad/cpp-1/public-2023-fall/decoder-attempt/"
    //        "english_letters.txt";
    auto holder = CollectHolder(path);
    std::string text;
    std::string trimmed_text;
    double dflt = log(1 / holder.sum);

    cout << "TEST_1" << endl;
    text = "ATTACK";
    trimmed_text = TrimText(text);
    cout << trimmed_text << endl;
    cout << EvaluatePermutation(trimmed_text, holder.map_grams, holder.map_chars, dflt);
    cout << endl;

    cout << "TEST_2" << endl;
    text = "ATTACK ON";
    trimmed_text = TrimText(text);
    cout << trimmed_text << endl;
    cout << EvaluatePermutation(trimmed_text, holder.map_grams, holder.map_chars, dflt);
    cout << endl;

    cout << "TEST_3" << endl;
    text = "ATTACK ON .D";
    trimmed_text = TrimText(text);
    cout << trimmed_text << endl;
    cout << EvaluatePermutation(trimmed_text, holder.map_grams, holder.map_chars, dflt);
    cout << endl;
}

void TestPermutateMap() {
    std::filesystem::path path =
        "/Users/dev.daniil.bakushkin/Desktop/shad/cpp-1/public-2023-fall/decoder-attempt/"
        "english_quadgrams.txt";

    int seed = 42;
    auto holder = CollectHolder(path);
    std::mt19937 gen(seed);
    auto curr_map = holder.map_chars;
    auto test_map = holder.map_chars;

    cout << "TEST_1" << endl;
    PrintOutMap(curr_map);
    cout << endl;
    PermutateMap(curr_map, &gen);
    PrintOutMap(curr_map);
    cout << endl;

    cout << "TEST_2" << endl;
    PrintOutMap(curr_map);
    cout << endl;
    PermutateMap(curr_map, &gen);
    PrintOutMap(curr_map);
    cout << endl;

    cout << "TEST_3" << endl;
    PrintOutMap(curr_map);
    cout << endl;
    for (int i = 0; i < 100; ++i) {
        PermutateMap(curr_map, &gen);
    }
    std::set<char> set_keys{};
    std::set<char> set_values{};
    for (const auto &[x, y] : curr_map) {
        set_keys.insert(x);
        set_values.insert(y);
    }
    if (set_keys.size() != set_values.size()) {
        std::runtime_error("Exception!");
    }
    if (set_keys.size() != ('z' - 'a' + 1)) {
        std::runtime_error("Exception!");
    }
    PrintOutMap(curr_map);
    cout << endl;

    cout << "TEST_4" << endl;
    PrintOutMap(curr_map);
    cout << endl;
    curr_map.clear();
    curr_map.insert(test_map.begin(), test_map.end());
    PrintOutMap(curr_map);
    if (test_map != curr_map) {
        std::runtime_error("Exception!");
    }
    cout << endl;
}

void TestCopyMap() {
    std::filesystem::path path =
        "/Users/dev.daniil.bakushkin/Desktop/shad/cpp-1/public-2023-fall/decoder-attempt/"
        "english_quadgrams.txt";
    auto holder = CollectHolder(path);
    std::string text;
    std::string trimmed_text;

    cout << "TEST_1" << endl;
    std::map<char, char> curr_map{};
    std::map<char, char> test_map{};
    CopyMap(holder.map_chars, curr_map);
    CopyMap(holder.map_chars, test_map);
    PrintOutMap(curr_map);
    cout << endl;
    PrintOutMap(test_map);
}

void TestFindPermutation() {
    std::filesystem::path path =
        "/Users/dev.daniil.bakushkin/Desktop/shad/cpp-1/public-2023-fall/decoder-attempt/"
        "english_quadgrams.txt";

    auto holder = CollectHolder(path);
    std::string text;
    std::string trimmed_text;
    std::map<char, char> decoded_map;

    cout << "TEST_1" << endl;
    text = "ATTACK THE EAST WALL ON DAWN";
    FindPermutation(text, holder);
    cout << endl;

    cout << "TEST_2" << endl;
    text = "ATTACK";
    FindPermutation(text, holder);
    cout << endl;
}

void TestUser1() {
    std::filesystem::path path =
        "/Users/dev.daniil.bakushkin/Desktop/shad/cpp-1/public-2023-fall/decoder-attempt/"
        "english_quadgrams.txt";

    auto holder = CollectHolder(path);
    std::string text;
    std::string trimmed_text;
    double metric;
    double dflt = log(1 / holder.sum);

    cout << "TEST_1" << endl;
    text = "ATTACK";
    trimmed_text = TrimText(text);
    metric = EvaluatePermutation(trimmed_text, holder.map_grams, holder.map_chars, dflt);
    cout << metric;
    cout << endl;

    cout << "TEST_2" << endl;
    text = "XJJXYZ";
    trimmed_text = TrimText(text);
    metric = EvaluatePermutation(trimmed_text, holder.map_grams, holder.map_chars, dflt);
    cout << metric;
    cout << endl;

    //    cout << "TEST_3" << endl;
    //    cout << holder.map_grams.at("xjjx") << endl;
    //    cout << holder.map_grams.at("jjxy") << endl;
    //    cout << holder.map_grams.at("jxyz") << endl;
    //    cout << endl;
    //    cout << holder.map_grams.at("atta") << endl;
    //    cout << holder.map_grams.at("ttac") << endl;
    //    cout << holder.map_grams.at("tack") << endl;
    //    cout << endl;

    cout << "TEST_3" << endl;
    std::string gram = "jjxy";
    if (holder.map_grams.find(gram) != holder.map_grams.end()) {
        std::cout << "here1" << endl;
    } else {
        std::cout << "here2" << endl;
    }
}

void TestUser2() {
    std::string text;
    char c;
    cout << "TEST_1" << endl;
    text = "A";
    c = std::tolower(text[0]);
    cout << c;
    cout << endl;

    cout << "TEST_2" << endl;
    text = "t";
    c = std::tolower(text[0]);
    cout << c;
    cout << endl;
}

void TestDecode() {

    std::string text;
    std::string trimmed_text;

    std::map<char, char> map{};
    char ch = 'a';
    while (ch <= 'z') {
        map[ch] = ch;
        ++ch;
    }

    cout << "TEST_1" << endl;
    text = "attack";
    cout << Decode(text, map);
    cout << endl;

    cout << "TEST_2" << endl;
    text = "attack._1attack";
    cout << Decode(text, map);
    cout << endl;

    cout << "TEST_3" << endl;
    text = "ATTAC ";
    cout << Decode(text, map);
    cout << endl;

    cout << "TEST_4" << endl;
    std::filesystem::path path =
        "/Users/dev.daniil.bakushkin/Desktop/shad/cpp-1/public-2023-fall/decoder-attempt/"
        "func_tests/romeo_and_juliet.txt";
    text = ReadTextFromFile(path);
    std::string text_decoded = Decode(text, map);
    if (text == text_decoded) {
        std::cout << "Success!";
    }
    cout << endl;

    cout << "TEST_5" << endl;
    map['q'] = 'a';
    text = "qTTQC ";
    cout << Decode(text, map);
    cout << endl;
}

bool TestUtils() {
    //    TestReadWriteFile();  // correct
    //    TestGrams();  // correct
    //    TestEvaluatePermutation();
    //    TestPermutateMap();
    //    TestCopyMap();
    //    TestFindPermutation();
    //    TestUser1();
    //    TestUser2();
    //    TestDecode();
    return true;
}

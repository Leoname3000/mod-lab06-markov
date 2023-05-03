// Copyright 2023 Leoname3000
#include <iostream>
#include <fstream>
#include <utility>
#include <vector>
#include <sstream>
#include <filesystem>
#include <cwctype>
#include "../include/textgen.h"

const int WORDS_PER_ROW = 10;

TextGenerator::TextGenerator(int prefixLength) {
    this->prefixLength = prefixLength;
}

void TextGenerator::LoadData(std::string fileName) {
    setlocale(LC_ALL, "");

    std::string referenceText = "";
    std::string row;

    std::string folderPath = std::filesystem::current_path().string();
    //std::cout << "Current root: " << folderPath << std::endl;
    std::string rootName = "mod-lab06-markov";
    int pos = folderPath.find(rootName);
    folderPath = folderPath.substr(0, pos + rootName.length()) + "/references/";
    std::string filePath = folderPath + fileName;

    std::ifstream f(filePath);
    if (f.is_open()) {
        while (getline(f, row)) {
            referenceText += " " + row;
        }
        f.close();
    } else {
        std::cout << "Can't open file" << std::endl;
    }

    std::stringstream strm(referenceText);
    std::vector<std::string> words;
    std::string word;
    while (getline(strm, word, ' ')) {
        char firstChar = word[0];
        char lastChar = word[word.length() - 1];
        char preLastChar = word[word.length() - 2];

        if (word.length() <= 0) { continue; }
        if (word.length() <= 1 && ispunct(lastChar)) { continue; }
        if ((wchar_t) lastChar == -108) { continue; }

        while (ispunct(firstChar) || (wchar_t) firstChar == -62) {
            if (ispunct(firstChar)) {
                word = word.substr(1, word.length() - 1);
            }
            if ((wchar_t) firstChar == -62) {
                word = word.substr(2, word.length() - 2);
            }
            firstChar = word[0];
        }

        while (ispunct(lastChar) ||
        (wchar_t) lastChar == -69 && (wchar_t) preLastChar == -62) {
            if (ispunct(lastChar)) {
                word = word.substr(0, word.length() - 1);
            }
            if ((wchar_t) lastChar == -69 && (wchar_t) preLastChar == -62) {
                word = word.substr(0, word.length() - 2);
            }
            lastChar = word[word.length() - 1];
            preLastChar = word[word.length() - 2];
        }

        words.push_back(word);
    }

    if (words.size() <= prefixLength) {
        throw std::invalid_argument("Text is shorter than prefix length!");
    }

    for (int i = prefixLength; i < words.size(); i++) {
        //std::cout << words[i] << std::endl;
        prefix pref;
        for (int p = prefixLength; p >= 1; p--) {
            pref.push_back(words[i-p]);
        }

        if (firstPrefix.empty()) {
            firstPrefix = pref;
        }

        if (statetab.find(pref) != statetab.end()) {
            suffixes currentSuff = statetab[pref];
            if (std::find(currentSuff.begin(), currentSuff.end(),
                          words[i]) == currentSuff.end()) {
                statetab[pref].push_back(words[i]);
            }
        } else {
            suffixes suff = suffixes();
            suff.push_back(words[i]);
            statetab[pref] = suff;
        }
    }

    //PrintTable();

    //std::cout << "FirstPrefix: ";
    //for (int i = 0; i < firstPrefix.size(); i++) {
    //    std::cout << firstPrefix[i] << " ";
    //}
    //std::cout << std::endl;
}

void TextGenerator::LoadData(table stateTable) {
    statetab = std::move(stateTable);
    if (firstPrefix.empty()) {
        firstPrefix = statetab.begin()->first;
    }
}

std::string TextGenerator::Generate(int length, int randSeed) {
    std::srand(randSeed);
    std::string text = "";
    prefix pref = firstPrefix;
    for (int i = 0; i < pref.size(); i++) {
        text += pref[i] + " ";
        if (i > 0 && i % WORDS_PER_ROW == 0) {
            text += "\n";
        }
    }
    for (int i = prefixLength + 1; i <= length; i++) {
        if (statetab.find(pref) == statetab.end()) {
            break;
        }
        suffixes suff = statetab[pref];
        int index = std::rand() % suff.size();
        //std::cout << index << std::endl;
        text += suff[index] + " ";
        if (i % WORDS_PER_ROW == 0) {
            text += "\n";
        }
        pref.pop_front();
        pref.push_back(suff[index]);
        //std::cout << text << std::endl;
    }
    return text;
}

table TextGenerator::GetTable() {
    return statetab;
}

void TextGenerator::PrintTable() {
    for (table::iterator iter = statetab.begin();
    iter != statetab.end(); iter++) {
        prefix p = iter->first;
        suffixes s = iter->second;
        std::cout << "PRF: ";
        for (int i = 0; i < p.size(); i++) {
            std::cout << p[i] << " ";
        }
        std::cout << "| SUF: ";
        for (int i = 0; i < s.size(); i++) {
            std::cout << s[i] << " ";
        }
        std::cout << std::endl;
    }
}

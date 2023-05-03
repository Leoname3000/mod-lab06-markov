// Copyright 2023 Leoname3000
#ifndef INCLUDE_TEXTGEN_H_
#define INCLUDE_TEXTGEN_H_

#include <iostream>
#include <string>
#include <deque>
#include <vector>
#include <map>

typedef std::deque<std::string> prefix;
typedef std::vector<std::string> suffixes;
typedef std::map<prefix, suffixes> table;

class TextGenerator {
 private:
    table statetab;
    int prefixLength;
    prefix firstPrefix;
 public:
    explicit TextGenerator(int prefixLength);
    void LoadData(std::string fileName);
    void LoadData(table stateTable);
    std::string Generate(int length, int randSeed);
    table GetTable();
    void PrintTable();
};

#endif  // INCLUDE_TEXTGEN_H_

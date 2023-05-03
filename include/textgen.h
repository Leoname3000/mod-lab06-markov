// Copyright 2023 Leoname3000
#ifndef MOD_LAB06_MARKOV_SRC_TEXTGEN_H_
#define MOD_LAB06_MARKOV_SRC_TEXTGEN_H_

#include <iostream>
#include <deque>
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

#endif //MOD_LAB06_MARKOV_SRC_TEXTGEN_H_
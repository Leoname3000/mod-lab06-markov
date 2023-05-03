// Copyright 2023 Leoname3000
#include "../include/textgen.h"

const int NPREF = 2;
const int MAXGEN = 1000;

int main() {
    TextGenerator tg = TextGenerator(NPREF);
    tg.LoadFile("teremok.txt");
    tg.LoadFile("kozaDereza.txt");
    tg.LoadFile("kolobok.txt");
    tg.LoadFile("goldenFish.txt");
    tg.LoadFile("chickenRyaba.txt");
    //tg.PrintTable();
    std::string text = tg.Generate(MAXGEN, 15);
    std::cout << text;
}

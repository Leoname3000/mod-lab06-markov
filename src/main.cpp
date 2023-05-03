// Copyright 2023 Leoname3000
#include "../include/textgen.h"

const int NPREF = 2;
const int MAXGEN = 1000;

int main() {
    TextGenerator tg = TextGenerator(NPREF);
    tg.LoadData("teremok.txt");
    tg.LoadData("kozaDereza.txt");
    tg.LoadData("kolobok.txt");
    tg.LoadData("goldenFish.txt");
    tg.LoadData("chickenRyaba.txt");
    //tg.PrintTable();
    std::string text = tg.Generate(MAXGEN, 15);
    std::cout << text;
}

// Copyright 2021 GHA Test Team
#include <gtest/gtest.h>
#include "../include/textgen.h"

TEST(TextGenerator, PrefixLength) {
    TextGenerator tg = TextGenerator(2);
    tg.LoadData("test.txt");
    table t = tg.GetTable();
    for (table::iterator iter = t.begin(); iter != t.end(); iter++) {
        prefix p = iter->first;
        EXPECT_EQ(2, p.size());
    }
}

TEST(TextGenerator, PrefixSuffix) {
    TextGenerator tg = TextGenerator(2);
    tg.LoadData("test.txt");
    table t = tg.GetTable();
    prefix p;
    p.push_back("With");
    p.push_back("great");
    EXPECT_EQ("power", t[p][0]);
}

TEST(TextGenerator, OneSuffix) {
    TextGenerator tg = TextGenerator(1);
    tg.LoadData("test.txt");
    table t = tg.GetTable();
    prefix p;
    p.push_back("With");
    suffixes s;
    s.push_back("great");
    EXPECT_EQ(s[0], t[p][0]);
}

TEST(TextGenerator, ManySuffixes) {
    TextGenerator tg = TextGenerator(1);
    tg.LoadData("test.txt");
    table t = tg.GetTable();
    prefix p;
    p.push_back("great");
    suffixes s;
    s.push_back("power");
    s.push_back("responsibility");
    EXPECT_EQ(s[0], t[p][0]);
    EXPECT_EQ(s[1], t[p][1]);
}

TEST(TextGenerator, ManualTable) {
    table t;
    prefix p1 = { "hello", "again" };
    suffixes s1 = { "hello" };
    t[p1] = s1;
    prefix p2 = { "again", "hello" };
    suffixes s2 = { "again" };
    t[p2] = s2;

    TextGenerator tg = TextGenerator(2);
    tg.LoadData(t);
    std::string text = tg.Generate(7, 0);
    std::string expected = "again hello again hello again hello again ";
    EXPECT_EQ(expected, text);
}

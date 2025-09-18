#include <gtest/gtest.h>
#include <filter.hpp>
#include <string>

TEST(test_01, RemovesAllVowels) {
    EXPECT_EQ(filter::Filter("hello world"), "hll wrld");
    EXPECT_EQ(filter::Filter("aeiou"), "");
    EXPECT_EQ(filter::Filter("AEIOU"), "");
}

TEST(test02, NoVowelsInString) {
    EXPECT_EQ(filter::Filter("bcdfghjklmnpqrstvwxyz"), "bcdfghjklmnpqrstvwxyz");
    EXPECT_EQ(filter::Filter("BCDFGHJKLMNPQRSTVWXYZ"), "BCDFGHJKLMNPQRSTVWXYZ");
    EXPECT_EQ(filter::Filter("1234567890!@#$%^&*()"), "1234567890!@#$%^&*()");
}

TEST(test03, MixedCaseVowels) {
    EXPECT_EQ(filter::Filter("Hello World"), "Hll Wrld");
    EXPECT_EQ(filter::Filter("ApplE jUicE"), "ppl jc");
    EXPECT_EQ(filter::Filter("AeIoUy"), "y");
}

TEST(test04, EmptyStringAndSpaces) {
    EXPECT_EQ(filter::Filter(""), "");
    EXPECT_EQ(filter::Filter("   "), "   ");
    EXPECT_EQ(filter::Filter(" a e i o u "), "      ");
}

TEST(test05, SpecialCharactersAndNumbers) {
    EXPECT_EQ(filter::Filter("hello123world!"), "hll123wrld!");
    EXPECT_EQ(filter::Filter("c++ is awesome!"), "c++ s wsm!");
    EXPECT_EQ(filter::Filter("test@mail.com"), "tst@ml.cm");
}

TEST(test06, LongStrings) {
    std::string longString = "a" + std::string(1000, 'e') + "b";
    EXPECT_EQ(filter::Filter(longString), "b");
    
    std::string noVowelsString = std::string(1000, 'b');
    EXPECT_EQ(filter::Filter(noVowelsString), noVowelsString);
}

TEST(test07, OnlyConsonants) {
    EXPECT_EQ(filter::Filter("bcdfg"), "bcdfg");
    EXPECT_EQ(filter::Filter("xyz"), "xyz");
    EXPECT_EQ(filter::Filter("qwrtpsdfghjklzxcvbnm"), "qwrtpsdfghjklzxcvbnm");
}

TEST(test08, EdgeCases) {
    EXPECT_EQ(filter::Filter("a"), "");
    EXPECT_EQ(filter::Filter("z"), "z");
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

#include <gtest/gtest.h>
#include "parser.h"

TEST(ParserTest, BasicAssertions) {
    std::string s("群馬県高崎市");
    Address address_parsed = address_parse(s);
    EXPECT_EQ("群馬", address_parsed.prefecture);
    EXPECT_EQ("高崎", address_parsed.municipality);
}

TEST(ParserTest, BasicAssertions2){
    std::string s("山梨県南巨摩郡身延町切石350");
    Address address_parsed = address_parse(s);
    EXPECT_EQ("山梨", address_parsed.prefecture);
    EXPECT_EQ("南巨摩", address_parsed.county);
    EXPECT_EQ("身延", address_parsed.municipality);
    EXPECT_EQ("切石", address_parsed.town);
    EXPECT_EQ("350", address_parsed.district);
}

TEST(ParserTest, BasicAssertions3){
    std::string s("奈良県奈良市雑司町129");
    Address address_parsed = address_parse(s);
    EXPECT_EQ("奈良", address_parsed.prefecture);
    EXPECT_EQ("奈良", address_parsed.municipality);
    EXPECT_EQ("雑司町", address_parsed.town);
    EXPECT_EQ("129", address_parsed.district);
}

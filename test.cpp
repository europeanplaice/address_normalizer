#include <gtest/gtest.h>
#include "parser.h"

TEST(ParserTest, KyotoAssertions) {
    std::string s("京都府京都市");
    Address address_parsed = address_parse(s);
    EXPECT_EQ("京都", address_parsed.prefecture);
    EXPECT_EQ("府", address_parsed.prefecture_suffix);
    EXPECT_EQ("京都", address_parsed.municipality);
    EXPECT_EQ("市", address_parsed.municipality_suffix);
}

TEST(ParserTest, KyotoAssertionsWard) {
    std::string s("京都府京都市右京区");
    Address address_parsed = address_parse(s);
    EXPECT_EQ("京都", address_parsed.prefecture);
    EXPECT_EQ("府", address_parsed.prefecture_suffix);
    EXPECT_EQ("京都", address_parsed.municipality);
    EXPECT_EQ("市", address_parsed.municipality_suffix);
    EXPECT_EQ("右京", address_parsed.ward);
}

TEST(ParserTest, KyotoAssertionsFull) {
    std::string s("京都府京都市中京区上本能寺前町488番地");
    Address address_parsed = address_parse(s);
    EXPECT_EQ("京都", address_parsed.prefecture);
    EXPECT_EQ("府", address_parsed.prefecture_suffix);
    EXPECT_EQ("京都", address_parsed.municipality);
    EXPECT_EQ("市", address_parsed.municipality_suffix);
    EXPECT_EQ("中京", address_parsed.ward);
    EXPECT_EQ("上本能寺前町", address_parsed.town);
    EXPECT_EQ("488番地", address_parsed.district);
}

TEST(ParserTest, BasicAssertions) {
    std::string s("群馬県高崎市");
    Address address_parsed = address_parse(s);
    EXPECT_EQ("群馬", address_parsed.prefecture);
    EXPECT_EQ("県", address_parsed.prefecture_suffix);
    EXPECT_EQ("高崎", address_parsed.municipality);
    EXPECT_EQ("市", address_parsed.municipality_suffix);
}

TEST(ParserTest, BasicAssertions2){
    std::string s("山梨県南巨摩郡身延町切石350");
    Address address_parsed = address_parse(s);
    EXPECT_EQ("山梨", address_parsed.prefecture);
    EXPECT_EQ("県", address_parsed.prefecture_suffix);
    EXPECT_EQ("南巨摩", address_parsed.county);
    EXPECT_EQ("身延", address_parsed.municipality);
    EXPECT_EQ("町", address_parsed.municipality_suffix);
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

TEST(ParserTest, BasicAssertions4){
    std::string s("東京都千代田区九段南1-2-1");
    Address address_parsed = address_parse(s);
    EXPECT_EQ("1", address_parsed.subarea);
    EXPECT_EQ("2", address_parsed.block);
    EXPECT_EQ("1", address_parsed.building_num);
}

TEST(ParserTest, BasicAssertions4_2){
    std::string s("東京都千代田区九段南1丁目2-1");
    Address address_parsed = address_parse(s);
    EXPECT_EQ("1", address_parsed.subarea);
    EXPECT_EQ("2", address_parsed.block);
    EXPECT_EQ("1", address_parsed.building_num);
}

TEST(ParserTest, BasicAssertions4_3){
    std::string s("東京都千代田区九段南1丁目2番1号");
    Address address_parsed = address_parse(s);
    EXPECT_EQ("東京", address_parsed.prefecture);
    EXPECT_EQ("都", address_parsed.prefecture_suffix);
    EXPECT_EQ("千代田", address_parsed.municipality);
    EXPECT_EQ("区", address_parsed.municipality_suffix);
    EXPECT_EQ("九段南", address_parsed.town);
    EXPECT_EQ("1", address_parsed.subarea);
    EXPECT_EQ("2", address_parsed.block);
    EXPECT_EQ("1", address_parsed.building_num);
}

TEST(ParserTest, Buildings){
    std::string s("東京都港区六本木6-10-1六本木ヒルズ森タワー53階");
    Address address_parsed = address_parse(s);
    EXPECT_EQ("東京", address_parsed.prefecture);
    EXPECT_EQ("都", address_parsed.prefecture_suffix);
    EXPECT_EQ("港", address_parsed.municipality);
    EXPECT_EQ("区", address_parsed.municipality_suffix);
    EXPECT_EQ("六本木", address_parsed.town);
    EXPECT_EQ("6", address_parsed.subarea);
    EXPECT_EQ("10", address_parsed.block);
    EXPECT_EQ("1", address_parsed.building_num);
    EXPECT_EQ("六本木ヒルズ森タワー", address_parsed.building_name);
    EXPECT_EQ("53", address_parsed.building_floor);
}

TEST(ParserTest, Buildings2){
    std::string s("東京都港区虎ノ門1丁目11日本財団第2ビル");
    Address address_parsed = address_parse(s);
    EXPECT_EQ("東京", address_parsed.prefecture);
    EXPECT_EQ("都", address_parsed.prefecture_suffix);
    EXPECT_EQ("港", address_parsed.municipality);
    EXPECT_EQ("区", address_parsed.municipality_suffix);
    EXPECT_EQ("虎ノ門", address_parsed.town);
    EXPECT_EQ("1", address_parsed.subarea);
    EXPECT_EQ("11", address_parsed.block);
    EXPECT_EQ("", address_parsed.building_num);
    EXPECT_EQ("日本財団第2ビル", address_parsed.building_name);
    EXPECT_EQ("", address_parsed.building_floor);
}

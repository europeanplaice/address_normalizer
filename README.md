# address_normalizer

Boost Qiを用いて住所を正規化します。

```cpp
Address address_parse(std::string address_string);
```

結果は `Address`構造体として返ります。
```cpp
struct Address {
    std::string prefecture; //都道府県
    std::string county; //郡
    std::string municipality; //市区町村
    std::string ward; //区行政区
    std::string town; //町名
    std::string district; //番地
    std::string prefecture_suffix; // 都道府県接尾辞
    std::string municipality_suffix; // 市区町村接尾辞
    std::string subarea; // 丁目
    std::string block; // 番   
    std::string building_num ; // 号 
    std::string building_name ; // ビル名
    std::string building_floor ; // ビル フロア
};
```

## 例(単体テストより抜粋)
```cpp

#include <gtest/gtest.h>
#include "parser.h"

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
```

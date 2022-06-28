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
};
```

## 例(単体テストより抜粋)
```cpp
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
```

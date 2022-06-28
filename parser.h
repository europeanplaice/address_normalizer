#include <boost/fusion/adapted/struct/adapt_struct.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/phoenix.hpp>

#include <iostream>
#include <string>
#include <tuple>

namespace qi = boost::spirit::qi;

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

BOOST_FUSION_ADAPT_STRUCT(
        Address,
    ( std::string, prefecture )
    ( std::string, county )
    ( std::string, municipality )
    ( std::string, ward )
    ( std::string, town )
    ( std::string, district )
    ( std::string, prefecture_suffix )
    ( std::string, municipality_suffix )
    ( std::string, subarea )
    ( std::string, block )
    ( std::string, building_num )
    ( std::string, building_name )
    ( std::string, building_floor )

        )

template<typename Iterator>
struct address_grammar : qi::grammar<Iterator, Address()>
{
    address_grammar() : address_grammar::base_type(rule)
    {
        using qi::standard_wide::char_;
        using qi::ascii::digit;
        using boost::phoenix::at_c;
        using boost::spirit::qi::lexeme;
        using boost::spirit::qi::hold;
        prefecture_suffix = ( 
                qi::string("都") |
                qi::string("道") |
                qi::string("府") |
                qi::string("県") );
        municipality_suffix = ( qi::string("市") | qi::string("区") | qi::string("町") | qi::string("村") );
        county_suffix = qi::lit("郡");
        ward_suffix = qi::lit("区");
        prefecture =
            ( qi::string("京都") >> qi::string("府") )
            | (+( char_ - prefecture_suffix ) >> prefecture_suffix);
        county = +( char_ - county_suffix ) >> county_suffix ;
        municipality = 
              ( qi::string("市川") >> qi::string("市") )
            | ( qi::string("市原") >> qi::string("市") )
            | ( qi::string("野々市") >> qi::string("市") )
            | ( qi::string("四日市") >> qi::string("市") )
            | ( qi::string("廿日市") >> qi::string("市") )
            | ( +( char_ - municipality_suffix ) >> municipality_suffix )
            ;
        ward = +( char_ - qi::lit("市") ) >> qi::lit("市") >> +( char_ - ward_suffix ) >> ward_suffix;
        town = +( char_ - digit );
        district = +char_;
        district_new = hold[+digit >> (qi::lit("-") | qi::lit("丁目")) >> +digit >> (qi::lit("-") | qi::lit("番") | qi::lit("番地")) >> +digit >> -qi::lit("号")];
        district_new_partial = hold[+digit >> (qi::lit("-") | qi::lit("丁目")) >> +digit >> -(qi::lit("-") | qi::lit("番") | qi::lit("番地"))];
        building_name = +(char_ - building_floor);
        building_floor = +digit >> (qi::lit("階") | qi::lit("F"));
        rule =
            (
             prefecture[at_c<0>(qi::_val) = qi::_1[0]][at_c<6>(qi::_val) = qi::_1[1]]
             >> county[at_c<1>(qi::_val) = qi::_1]
             >> municipality[at_c<2>(qi::_val) = qi::_1[0]][at_c<7>(qi::_val) = qi::_1[1]]
             >> town[at_c<4>(qi::_val) = qi::_1]
             >> district[at_c<5>(qi::_val) = qi::_1]
             )

            |
             ( prefecture[at_c<0>(qi::_val) = qi::_1[0]][at_c<6>(qi::_val) = qi::_1[1]]
              >> ward[at_c<2>(qi::_val) = qi::_1[0]][at_c<3>(qi::_val) = qi::_1[1]][at_c<7>(qi::_val) = "市"]
              >> town[at_c<4>(qi::_val) = qi::_1]
             >> district[at_c<5>(qi::_val) = qi::_1]
              )[at_c<1>(qi::_val) = ""]

            |
            ( prefecture[at_c<0>(qi::_val) = qi::_1[0]][at_c<6>(qi::_val) = qi::_1[1]]
              >> municipality[at_c<2>(qi::_val) = qi::_1[0]][at_c<7>(qi::_val) = qi::_1[1]]
              >> town[at_c<4>(qi::_val) = qi::_1]
             >> 
             (
                  district_new[at_c<8>(qi::_val) = qi::_1[0]][at_c<9>(qi::_val) = qi::_1[1]][at_c<10>(qi::_val) = qi::_1[2]] 
                | district_new_partial[at_c<8>(qi::_val) = qi::_1[0]][at_c<9>(qi::_val) = qi::_1[1]] 
                | district[at_c<5>(qi::_val) = qi::_1])
             >> building_name[at_c<11>(qi::_val) = qi::_1]
             >> building_floor[at_c<12>(qi::_val) = qi::_1]
              )[at_c<1>(qi::_val) = ""]
            ;
    }

    qi::rule<Iterator, std::string()> prefecture_suffix;
    qi::rule<Iterator, std::string()> municipality_suffix;
    qi::rule<Iterator, void()> county_suffix;
    qi::rule<Iterator, void()> ward_suffix;
    qi::rule<Iterator, std::vector<std::string>()> prefecture;
    qi::rule<Iterator, std::string()> county;
    qi::rule<Iterator, std::vector<std::string>()> municipality;
    qi::rule<Iterator, std::string()> town;
    qi::rule<Iterator, std::string()> district;
    qi::rule<Iterator, std::string()> building_name;
    qi::rule<Iterator, std::string()> building_floor;
    qi::rule<Iterator, std::vector<std::string>()> district_new;
    qi::rule<Iterator, std::vector<std::string>()> district_new_partial;
    qi::rule<Iterator, std::vector<std::string>()> ward;
    qi::rule<Iterator, Address()> rule;
};

Address address_parse(std::string address_string);

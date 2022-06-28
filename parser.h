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
    std::string ward; //区
    std::string town; //町名
    std::string district; //番地
    std::string prefecture_suffix; //都道府県
    std::string municipality_suffix; //

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

        )

template<typename Iterator>
struct address_grammar : qi::grammar<Iterator, Address()>
{
    address_grammar() : address_grammar::base_type(rule)
    {
        using qi::standard_wide::char_;
        using qi::ascii::digit;
        using boost::phoenix::at_c;
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
              ( qi::string("京都") >> qi::string("市") )
            | ( qi::string("市川") >> qi::string("市") )
            | ( qi::string("市原") >> qi::string("市") )
            | ( qi::string("野々市") >> qi::string("市") )
            | ( qi::string("四日市") >> qi::string("市") )
            | ( qi::string("廿日市") >> qi::string("市") )
            | ( +( char_ - municipality_suffix ) >> municipality_suffix )
            ;
        ward = +( char_ - qi::lit("市") ) >> qi::lit("市") >> +( char_ - ward_suffix ) >> ward_suffix;
        town = +( char_ - digit );
        district = +char_;
        rule =
            (
             prefecture[at_c<0>(qi::_val) = qi::_1[0]][at_c<6>(qi::_val) = qi::_1[1]]
             >> county[at_c<1>(qi::_val) = qi::_1]
             >> municipality[at_c<2>(qi::_val) = qi::_1[0]][at_c<7>(qi::_val) = qi::_1[1]]
             >> -town[at_c<4>(qi::_val) = qi::_1]
             >> -district[at_c<5>(qi::_val) = qi::_1]
             )

            |
             ( prefecture[at_c<0>(qi::_val) = qi::_1[0]][at_c<6>(qi::_val) = qi::_1[1]]
              >> ward[at_c<2>(qi::_val) = qi::_1[0]][at_c<3>(qi::_val) = qi::_1[1]][at_c<7>(qi::_val) = "市"]
              >> -town[at_c<4>(qi::_val) = qi::_1]
             >> -district[at_c<5>(qi::_val) = qi::_1]
              )[at_c<1>(qi::_val) = ""]
              
            |
            ( prefecture[at_c<0>(qi::_val) = qi::_1[0]][at_c<6>(qi::_val) = qi::_1[1]]
              >> municipality[at_c<2>(qi::_val) = qi::_1[0]][at_c<7>(qi::_val) = qi::_1[1]]
              >> -town[at_c<4>(qi::_val) = qi::_1]
             >> -district[at_c<5>(qi::_val) = qi::_1]
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
    qi::rule<Iterator, std::vector<std::string>()> ward;
    qi::rule<Iterator, Address()> rule;
};

Address address_parse(std::string address_string);

#include "parser.h"

Address address_parse(std::string address_string)
{
    typedef std::string::const_iterator iterator_type;
    typedef address_grammar<iterator_type> address_grammar;
    Address address_parsed;
    address_grammar address_grammar_instance;
    std::string::const_iterator iter = address_string.begin(), end = address_string.end();
    bool r = parse(iter, end, address_grammar_instance, address_parsed);
    return address_parsed;
}

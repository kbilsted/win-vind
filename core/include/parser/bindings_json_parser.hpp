#ifndef _BINDINGS_JSON_PARSER_HPP
#define _BINDINGS_JSON_PARSER_HPP

#include "bind/binded_func.hpp"
#include "bind/logger_parser.hpp"

#include "mapdefs.hpp"

namespace vind
{
    namespace bindjsonparser {
        void parse_bindings_as_list(
                const std::string& filepath,
                const std::vector<BindedFunc::SPtr>& all_func_list,
                ParsedStringBindingLists& parsed_bindings) ;
    }
}

#endif

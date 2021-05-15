#include "bind/syscmd/set.hpp"

#include <iostream>
#include <string>

#include "bind/binded_func.hpp"
#include "bind/binded_func_creator.hpp"
#include "g_params.hpp"
#include "key/char_logger.hpp"
#include "opt/virtual_cmd_line.hpp"
#include "parser/rc_parser.hpp"
#include "util/def.hpp"
#include "util/string.hpp"

namespace vind
{
    SyscmdSet::SyscmdSet()
    : BindedFuncCreator("system_command_set")
    {}

    void SyscmdSet::sprocess(const std::string& args) {
        if(args.empty()) {
            VirtualCmdLine::msgout("E: Not support list of option yet") ;
            return ;
        }

        auto [key, val] = rcparser::divide_key_and_value(args, "=") ;
        key = util::A2a(key) ;

        if(val.empty()) { // set option_name
            if(key.size() > 2 && key[0] == 'n' && key[1] == 'o') {
                gparams::set(key.substr(2), false) ;
            }
            else {
                gparams::set(key, true) ;
            }
        }
        else { // set option_name = value
            if(val.find_first_not_of("0123456789.") == std::string::npos) {
                gparams::set(key, std::stod(val)) ;
            }
            else {
                gparams::set(key, val) ;
            }
        }
    }

    void SyscmdSet::sprocess(NTypeLogger&) {
        return ;
    }

    void SyscmdSet::sprocess(const CharLogger& parent_lgr) {
        std::cout << "called\n" ;
        auto str = parent_lgr.to_str() ;
        if(str.empty()) {
            return ;
        }

        auto [cmd, args] = rcparser::divide_cmd_and_args(str) ;
        sprocess(args) ;
    }
}

#include "search_pattern.hpp"
#include "keybrd_eventer.hpp"
#include "utility.hpp"

#include <iostream>
using namespace std ;

//SearchPattern
const string SearchPattern::sname() noexcept
{
    return "search_pattern" ;
}

void SearchPattern::sprocess(
        const bool first_call,
        const unsigned int UNUSED(repeat_num),
        VKCLogger* const UNUSED(parent_vkclgr),
        const CharLogger* const UNUSED(parent_charlgr))
{
    if(first_call)
        KeybrdEventer::pushup(VKC_F3) ;
}

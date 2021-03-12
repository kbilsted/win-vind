#ifndef _PAGER_HPP
#define _PAGER_HPP

#include "binded_func_with_creator.hpp"

struct Move2NextPage : public BindedFuncWithCreator<Move2NextPage>
{
    static void sprocess(
            const bool first_call,
            const unsigned int repeat_num,
            VKCLogger* const parent_vkclgr,
            const CharLogger* const parent_charlgr) ;
    static const std::string sname() noexcept ;
} ;

struct Move2PrevPage : public BindedFuncWithCreator<Move2PrevPage>
{
    static void sprocess(
            const bool first_call,
            const unsigned int repeat_num,
            VKCLogger* const parent_vkclgr,
            const CharLogger* const parent_charlgr) ;
    static const std::string sname() noexcept ;
} ;
#endif

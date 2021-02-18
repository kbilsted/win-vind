#include "external_app.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <windows.h>

#include "disable_gcc_warning.hpp"
#include <nlohmann/json.hpp>
#include "enable_gcc_warning.hpp"

#include "jump_cursor.hpp"
#include "key_logger.hpp"
#include "keybrd_eventer.hpp"
#include "msg_logger.hpp"
#include "path.hpp"
#include "utility.hpp"
#include "virtual_cmd_line.hpp"

namespace ExAppUtility
{
    using mss_t = std::unordered_map<std::string, std::string> ;
    inline static const mss_t _load_proc_list_core() {
        mss_t map{} ;

        nlohmann::json j ;
        std::ifstream ifs(Path::SETTINGS()) ;
        ifs >> j ;

        for(const auto& i : j.at("exapps").at("choices")) {
            try {
                auto&& key = i.at("name").get<std::string>() ;
                auto&& val = i.at("value").get<std::string>() ;
                map[key]   = val ;
            }
            catch(const std::exception& e) {
                ERROR_PRINT(std::string(e.what()) + ", so one shortcut application is skipped.") ;
                continue ;
            }
        }
        return map ;
    }

    static mss_t g_proc_list{} ;
    void load_config() {
        g_proc_list = _load_proc_list_core() ;
    }
}

using namespace ExAppUtility ;

//StartShell
const std::string StartShell::sname() noexcept
{
    return "start_shell" ;
}

void StartShell::sprocess(
        const bool first_call,
        const unsigned int UNUSED(repeat_num),
        KeyLogger* UNUSED(parent_vkclgr),
        const KeyLogger* const UNUSED(parent_charlgr))
{
    if(!first_call) return ;
    try {
        Utility::create_process(Path::HOME_PATH(), g_proc_list.at("shell")) ;
    }
    catch(const std::out_of_range&) {
        VirtualCmdLine::msgout("e: Not a command") ;
        return ;
    }

    Sleep(100) ; //wait until select window by OS.
    Jump2ActiveWindow::sprocess(true, 1, nullptr, nullptr) ;
}


/*
 * -- ToDo --
 * connect directly to command prompt
 *
 */

//StartAnyApp
const std::string StartAnyApp::sname() noexcept
{
    return "start_any_app" ;
}

void StartAnyApp::sprocess(
        const bool first_call,
        const unsigned int UNUSED(repeat_num),
        KeyLogger* UNUSED(parent_vkclgr),
        const KeyLogger* const parent_charlgr)
{
    if(!first_call) return ;

    if(!parent_charlgr)
        throw LOGIC_EXCEPT("The passed parent logger is null") ;

    auto cmd = KyLgr::log2str(*parent_charlgr) ;
    if(!cmd.empty()) {
        try {
            Utility::create_process(".", g_proc_list.at(cmd.substr(1))) ;
        }
        catch(const std::out_of_range&) {
            VirtualCmdLine::msgout("e: Not a command") ;
            return ;
        }

        Sleep(100) ; //wait until select window by OS.
        Jump2ActiveWindow::sprocess(true, 1, nullptr, nullptr) ;
    }
}


//StartExplorer
const std::string StartExplorer::sname() noexcept
{
    return "start_explorer" ;
}

void StartExplorer::sprocess(
        const bool first_call,
        const unsigned int UNUSED(repeat_num),
        KeyLogger* UNUSED(parent_vkclgr),
        const KeyLogger* const UNUSED(parent_charlgr))
{
    if(!first_call) return ;
    //_create_process("explorer") ;
    KeybrdEventer::pushup(VKC_LWIN, VKC_E) ;

    Sleep(100) ; //wait until select window by OS.
    Jump2ActiveWindow::sprocess(true, 1, nullptr, nullptr) ;
}

//OpenStartMenu
const std::string OpenStartMenu::sname() noexcept
{
    return "open_start_menu" ;
}

void OpenStartMenu::sprocess(
        const bool first_call,
        const unsigned int UNUSED(repeat_num),
        KeyLogger* UNUSED(parent_vkclgr),
        const KeyLogger* const UNUSED(parent_charlgr))
{
    if(!first_call) return ;
    KeybrdEventer::pushup(VKC_LWIN) ;
    Sleep(100) ; //wait until select window by OS.
    Jump2ActiveWindow::sprocess(true, 1, nullptr, nullptr) ;
}

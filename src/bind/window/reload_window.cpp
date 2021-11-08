#include "reload_window.hpp"

#include "core/ntype_logger.hpp"
#include "util/def.hpp"
#include "util/keybrd.hpp"

namespace vind
{
    //ReloadCurrentWindow
    ReloadCurrentWindow::ReloadCurrentWindow()
    : BindedFuncCreator("reload_current_window")
    {}
    void ReloadCurrentWindow::sprocess() {
        util::pushup(KEYCODE_F5) ;
    }
    void ReloadCurrentWindow::sprocess(NTypeLogger& parent_lgr) {
        if(!parent_lgr.is_long_pressing()) {
            sprocess() ;
        }
    }
    void ReloadCurrentWindow::sprocess(const CharLogger& UNUSED(parent_lgr)) {
        sprocess() ;
    }
}
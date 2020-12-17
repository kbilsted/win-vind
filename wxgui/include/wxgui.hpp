#ifndef _WXGUI_HPP
#define _WXGUI_HPP

#include "disable_gcc_warning.hpp"
#include <wx/app.h>
#include "enable_gcc_warning.hpp"

#include <memory>

namespace wxGUI
{
    class App : public wxApp
    {
    private:
        virtual bool OnInit() override ;
        virtual int MainLoop() override ;

    public:
        virtual ~App() noexcept ;
    } ;
}

#endif

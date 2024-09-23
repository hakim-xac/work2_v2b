#pragma once

#include "common.h"
#include "window_handler.h"

namespace LAB
{
    class Window final {
    public:
        //--------------------------

        using fn_t = LRESULT(*)(HWND, UINT, WPARAM, LPARAM);

        explicit Window(
            HINSTANCE hinstance,
            HINSTANCE hprev_instance,
            LPWSTR lpcmd_line,
            int ncmd_show,
            int32_t pos_x_window,
            int32_t pos_y_window,
            int32_t width_window,
            int32_t height_window
        );

        //--------------------------

        void loop() const;

        //--------------------------
        
        [[nodiscard]] HWND getHWND() const noexcept;
        
        //--------------------------

    private:

        //--------------------------

        [[nodiscard]]
        bool init(
            int32_t pos_x_window,
            int32_t pos_y_window,
            int32_t width_window,
            int32_t height_window
        );

        //--------------------------

        bool initInstance(
            int32_t pos_x_window,
            int32_t pos_y_window,
            int32_t width_window,
            int32_t height_window
        );

        //--------------------------

        ATOM myRegisterClass(HINSTANCE hinstance);

        //--------------------------

    private:
        static constexpr size_t MAX_LOADSTRING{ 100 };
        WCHAR m_title[MAX_LOADSTRING];
        WCHAR m_window_classname[MAX_LOADSTRING];
        HINSTANCE m_hinst;
        HINSTANCE m_hprev_inst;
        fn_t m_func;
        LPWSTR m_lpcmd_line;
        int m_ncmd_show;
        HWND m_hwnd;
        std::unique_ptr<WindowHandler> m_window_handler_uptr;
    };
}

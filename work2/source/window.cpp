#pragma once

#include "../include/window.h"
#include "../include/resource.h"
#include <thread>

namespace LAB 
{
    //--------------------------

    Window::Window(
        HINSTANCE hinstance,
        HINSTANCE hprev_instance,
        LPWSTR lpcmd_line,
        int ncmd_show,
        int32_t pos_x_window,
        int32_t pos_y_window,
        int32_t width_window,
        int32_t height_window
        ) :
        m_hinst{ hinstance },
        m_hprev_inst{ hprev_instance },
        m_func{ LAB::WindowHandler::WndProc },
        m_lpcmd_line{ lpcmd_line },
        m_ncmd_show{ ncmd_show },
        m_window_handler_uptr{}
    {
        if (init(pos_x_window, pos_y_window, width_window, height_window) == false) [[unlikely]]
            throw std::runtime_error("Can not init Class Window!");

        m_window_handler_uptr = std::make_unique<WindowHandler>(m_hwnd);
    }

    //--------------------------

    void Window::loop() const
    {
        HACCEL hAccelTable{ LoadAccelerators(m_hinst, MAKEINTRESOURCE(IDC_WORK2)) };

        MSG msg{};

        while (GetMessage(&msg, nullptr, 0, 0))
        {
            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
    }

    //--------------------------
    
    [[nodiscard]]
    HWND
    Window::getHWND() const noexcept
    {
        return m_hwnd;
    }

    //--------------------------

    [[nodiscard]]
    bool Window::init(
        int32_t pos_x_window,
        int32_t pos_y_window,
        int32_t width_window,
        int32_t height_window
    )
    {
        UNREFERENCED_PARAMETER(m_hprev_inst);
        UNREFERENCED_PARAMETER(m_lpcmd_line);

        LoadStringW(m_hinst, IDS_APP_TITLE, m_title, MAX_LOADSTRING);
        LoadStringW(m_hinst, IDC_WORK2, m_window_classname, MAX_LOADSTRING);
        myRegisterClass(m_hinst);

        if (initInstance(pos_x_window, pos_y_window, width_window, height_window) == false) [[unlikely]]
            return false;

        return true;
    }

    //--------------------------
    
    [[nodiscard]]
    bool Window::initInstance(
        int32_t pos_x_window,
        int32_t pos_y_window,
        int32_t width_window,
        int32_t height_window
    )
    {
        HWND hWnd { 
            CreateWindowW(
                m_window_classname,
                m_title, 
                WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
                pos_x_window,
                pos_y_window,
                width_window,
                height_window,
                nullptr,
                nullptr
                , m_hinst,
                nullptr
            )
        };

        if (!hWnd) [[unlikely]]
            return false;

        ShowWindow(hWnd, m_ncmd_show);
        UpdateWindow(hWnd);

        return true;
    }
    
    //--------------------------
    
    ATOM Window::myRegisterClass(HINSTANCE hInstance)
    {
        WNDCLASSEXW wcex{};

        wcex.cbSize = sizeof(WNDCLASSEX);

        wcex.style = CS_HREDRAW | CS_VREDRAW;
        wcex.lpfnWndProc = m_func;
        wcex.cbClsExtra = 0;
        wcex.cbWndExtra = 0;
        wcex.hInstance = hInstance;
        wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WORK2));
        wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
        wcex.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
        wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_WORK2);
        wcex.lpszClassName = m_window_classname;
        wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

        return RegisterClassExW(&wcex);
    }

    //--------------------------
}
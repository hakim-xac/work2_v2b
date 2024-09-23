#include "../include/window_handler.h"
#include "../include/resource.h"
#include "../include/HdcScoped.h"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <memory>

namespace LAB
{
	//--------------------------
	
    WindowHandler::WindowHandler(HWND hwnd) :
        m_hwnd{ hwnd },
        m_hdc { GetDC(m_hwnd) }
    {
        CreateThread(0, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(fuelProcurementPointThread), 0, 0, &m_thread_id);
    }

	//--------------------------
	
    WindowHandler::~WindowHandler()
    {
        ReleaseDC(m_hwnd, m_hdc);
    }
    
    //--------------------------
	
    LRESULT CALLBACK
        WindowHandler::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
    {
        switch (message)
        {
        case WM_CREATE:
            SetTimer(hWnd, 1, 20, nullptr);
            break;
        case WM_TIMER:
            InvalidateRect(hWnd, nullptr, false);
            break;
        case WM_COMMAND:
        {
            int wmId{ LOWORD(wParam) };
            switch (wmId)
            {
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
        case WM_PAINT:
        {
            LAB::HdcScoped hdc_scoped{ hWnd };
            HDC hdc{ hdc_scoped.getHDC() };
            g_drawer.draw(hdc);
        }
        break;
        case WM_DESTROY:
            m_is_running = false;
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
        return 0;
    }

	//--------------------------
     
    void WindowHandler::fuelProcurementPointThread()
    {
        g_drawer.drawRectangle(40, 80, 100, 80, Color{ 200, 200, 200 });

        HANDLE boiler_provider{ CreateFileW(L"\\\\.\\pipe\\BoilerProvider", GENERIC_READ, 0, 0, OPEN_EXISTING, 0, 0) };
        HANDLE provider_transporter{ CreateFileW(L"\\\\.\\pipe\\ProviderTransporter", GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, 0, 0) };

        auto random_lambda { [](int32_t left_range, int32_t right_range)
        {
            std::default_random_engine re{ std::invoke(std::random_device{}) };
            std::uniform_int_distribution<int32_t> uniform_dist{ left_range, right_range };
            return uniform_dist(re);
        } };

        std::this_thread::sleep_for(std::chrono::milliseconds{ 1500 });

        unsigned long s{};
        unsigned long s2{};
        PipeMessage pipe_message{};
        WriteFile(provider_transporter, &pipe_message, sizeof pipe_message, &s, 0);
        if (s == 0)
            ExitProcess(0);

        while (m_is_running)
        {
            int32_t capacity{ std::invoke(random_lambda, 0, 7) + 5 };

            for (int32_t i{}; i < capacity; ++i)
            {
                g_drawer.drawRectangle(40, 85 + i * 20, 99, 85 + i * 20 + 19, Color{ 200, 240, 200 });

                std::this_thread::sleep_for(std::chrono::milliseconds{ 250 });
            }

            static_cast<void>(ReadFile(provider_transporter, &s2, 4, &s, 0));
            if (s == 0)
            {
                m_is_running = false;
                break;
            }

            int32_t boiler_number{ };

            static_cast<void>(ReadFile(boiler_provider, &boiler_number, 4, &s, 0));

            for (int32_t i{ capacity - 1 }; i >= 0; --i)
            {
                g_drawer.drawRectangle(40, 85 + i * 20, 99, 85 + i * 20 + 19, Color{ 255, 255, 255 });
                std::this_thread::sleep_for(std::chrono::milliseconds{ 100 });
            }

            pipe_message.capacity = capacity;
            pipe_message.boiler_number = boiler_number;

            WriteFile(provider_transporter, &pipe_message, sizeof pipe_message, &s, 0);
            if (s == 0)
            {
                m_is_running = false;
                break;
            }
        }

        ExitProcess(0);
    }

	//--------------------------
}
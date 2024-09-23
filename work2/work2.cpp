#include "include/framework.h"
#include "include/window.h"
#include "include/common.h"
#include "include/Drawer.h"

//--------------------------

LAB::Drawer g_drawer{};

//--------------------------

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    try
    {
        LAB::Window window{
            hInstance,
            hPrevInstance,
            lpCmdLine,
            nCmdShow,
            100, // start_pos_x
            100, // start_pos_y
            600, // width
            500, // height
        };

        window.loop();
    }
    catch (const std::exception& ex)
    {
        std::wcerr << L"Exception: " << ex.what() << "\n";
        return 1;
    }

    return 0;
}
#pragma once

#include "common.h"
#include "Drawer.h"
#include "Structs.h"

//--------------------------
extern LAB::Drawer g_drawer;
//--------------------------
namespace LAB
{

	class WindowHandler final
	{
	public:

		//--------------------------
		
		explicit WindowHandler(HWND hwnd);
		
		//--------------------------
		
		~WindowHandler();

		//--------------------------
		
		static void fuelProcurementPointThread();

		//--------------------------
		
		static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

		//--------------------------

	private:

		HWND m_hwnd;
		HDC m_hdc;
		mutable std::mutex m_draw_mx;
		std::unordered_map<size_t, std::jthread> m_threads;

		static inline unsigned long m_thread_id { 0 };
		static inline std::atomic_bool m_is_running{ true };
		static inline HANDLE sg_provider_transporter{};
		static inline HANDLE sg_boiler_provider{};
		static inline PipeMessage sg_pipe_message{};
	};
}

#include "../include/HdcScoped.h"

namespace LAB
{
	//--------------------------

	HdcScoped::HdcScoped(HWND hWnd) : 
		m_hwnd { hWnd },
		m_ps {},
		m_hdc { BeginPaint(m_hwnd, &m_ps) }
	{

	}

	//--------------------------

	HdcScoped::~HdcScoped()
	{
		ValidateRect(m_hwnd, NULL);
		EndPaint(m_hwnd, &m_ps);
	}

	//--------------------------
	
	[[nodiscard]] HDC HdcScoped::getHDC() const noexcept
	{
		return m_hdc;
	}

	//--------------------------
}
#pragma once

#include "common.h"

namespace LAB
{
	class HdcScoped final
	{
	public:
		explicit HdcScoped(HWND hWnd);
		~HdcScoped();

		HdcScoped(const HdcScoped&) = delete;
		HdcScoped(HdcScoped&&) = delete;

		HdcScoped& operator = (const HdcScoped&) = delete;
		HdcScoped& operator = (HdcScoped&&) = delete;

		[[nodiscard]] HDC getHDC() const noexcept;
	private:
		HWND m_hwnd;
		PAINTSTRUCT m_ps;
		HDC m_hdc;
	};

}

#include "../../include/objects/Rectangle.h"

namespace LAB 
{
	Rectangle::Rectangle(size_t pos_x, size_t pos_y, size_t width, size_t height, Color color) :
		m_pos_x{ pos_x },
		m_pos_y{ pos_y },
		m_width{ width },
		m_height{ height },
		m_color{ std::move(color) }
	{

	}
	void Rectangle::draw(HDC hdc) const
	{
		RECT r {
		   .left = static_cast<LONG>(m_pos_x),
		   .top = static_cast<LONG>(m_pos_y),
		   .right = static_cast<LONG>(m_width),
		   .bottom = static_cast<LONG>(m_height)
		};

		HBRUSH hBrush{ CreateSolidBrush(RGB(m_color.r, m_color.g, m_color.b)) };
		FillRect(hdc, &r, hBrush);
	}
}
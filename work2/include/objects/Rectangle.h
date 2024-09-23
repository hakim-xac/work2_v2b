#pragma once

#include "../common.h"
#include "Objects.h"
#include "Color.h"

namespace LAB
{
	class Rectangle final : public Objects {
	public: 
		explicit Rectangle(size_t pos_x, size_t pos_y, size_t width, size_t height, Color color);
		void draw(HDC hdc) const override;
	private:
		Color m_color;
		size_t m_pos_x;
		size_t m_pos_y;
		size_t m_width;
		size_t m_height;
	};
}
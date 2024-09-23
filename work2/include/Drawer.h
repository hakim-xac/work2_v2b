#pragma once

#include "common.h"
#include "objects/Objects.h"
#include "objects/Color.h"

namespace LAB
{
	class Drawer
	{
	public:
		void drawRectangle(size_t pos_x, size_t pos_y, size_t width, size_t height, Color color);

		void draw(HDC hdc);
	private:

		mutable std::mutex m_draw_mx;
		std::queue<std::unique_ptr<Objects>> m_data_objects;
	};
}


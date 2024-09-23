#include "../include/Drawer.h"
#include "../include/objects/Rectangle.h"

namespace LAB 
{
	void Drawer::drawRectangle(size_t pos_x, size_t pos_y, size_t width, size_t height, Color color)
	{
		std::lock_guard lk{ m_draw_mx };
		m_data_objects.push(std::make_unique<Rectangle>(pos_x, pos_y, width, height, color));
	}

	void Drawer::draw(HDC hdc)
	{
		std::lock_guard lk{ m_draw_mx };
		for (;!m_data_objects.empty(); m_data_objects.pop())
		{
			auto elem{ std::move(m_data_objects.front()) };

			elem.get()->draw(hdc);
		}
	}
}

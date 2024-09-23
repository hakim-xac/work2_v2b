#pragma once

namespace LAB
{
	class Objects {
	public:
		virtual ~Objects() = default;
		virtual void draw(HDC hdc) const = 0;
	};
}
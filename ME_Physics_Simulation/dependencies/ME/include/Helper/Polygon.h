#pragma once

#include <vector>

#include "../Helper/Vector2i.h"
#include "../Rendering/Scanline.h"

namespace ME
{
	class Polygon final
	{
	public:

		Polygon();
		Polygon(std::vector<Vector2f> vertices);

		unsigned int GetWidth() const;
		unsigned int GetHeight() const;
		int GetMinX() const;
		int GetMinY() const;
		int GetMaxX() const;
		int GetMaxY() const;
		std::vector<Vector2f> GetFilled() const;
		std::vector<Vector2f> GetVertices() const;

	private:

		std::vector<Vector2f> m_Vertices;
	
	};
}


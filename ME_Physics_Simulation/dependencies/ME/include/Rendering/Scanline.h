#pragma once

#include <vector>

#include "../Helper/Vector2i.h"
#include "../Helper/Vector2f.h"

namespace ME
{
	std::vector<Vector2f> Scanline(std::vector<Vector2f> verts, unsigned int w, unsigned int h);

	void AssignMinMaxXY(std::vector<Vector2f> verts, float& minX, float& maxX, float& minY, float& maxY);
}

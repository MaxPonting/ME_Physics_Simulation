#pragma once

#include "ComponentRef.h"
#include "../User/Texture.h"
#include "../Helper/RGBA.h"
#include "../Helper/Polygon.h"

namespace ME
{
	class PolygonRenderer final : public ComponentRef
	{
	public:

		PolygonRenderer();
		PolygonRenderer(unsigned int id, ECS* ecs);

		void SetPolygon(Polygon polygon);
		void SetColour(RGBA colour);
		void SetLayer(int layer);

		Polygon GetPolygon(Polygon polygon);
		RGBA GetColour();
		int GetLayer();
	};
}


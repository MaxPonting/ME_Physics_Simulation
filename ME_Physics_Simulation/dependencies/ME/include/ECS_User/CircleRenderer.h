#pragma once

#include "ComponentRef.h"
#include "../User/Texture.h"
#include "../Helper/RGBA.h"

namespace ME
{
	class CircleRenderer final : public ComponentRef
	{
	public:

		CircleRenderer();
		CircleRenderer(unsigned int id, ECS* ecs);

		void SetRadius(unsigned int radius);
		void SetColour(RGBA colour);
		void SetLayer(int layer);

		unsigned int GetRadius();
		RGBA GetColour();
		int GetLayer();	
	};
}


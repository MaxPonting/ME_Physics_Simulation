#pragma once

#include "ComponentRef.h"
#include "../User/Texture.h"
#include "../Helper/RGBA.h"

namespace ME
{
	class SpriteRenderer final : public ComponentRef
	{
	public:

		SpriteRenderer();
		SpriteRenderer(unsigned int id, ECS* ecs);

		void SetTexture(Texture texture);
		void SetColour(RGBA colour);
		void SetLayer(int layer);

		Texture GetTexture();
		RGBA GetColour();
		int GetLayer();

	};
}

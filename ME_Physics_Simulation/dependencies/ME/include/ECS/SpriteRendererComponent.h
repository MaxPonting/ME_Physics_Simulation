#pragma once

#include "Component.h"
#include "../User/Texture.h"
#include "../Helper/RGBA.h"

namespace ME
{
	class SpriteRendererComponent : public Component
	{
	public:

		SpriteRendererComponent();
		SpriteRendererComponent(unsigned int entityID);

		Texture texture;
		RGBA colour;
		int layer;

	};
}



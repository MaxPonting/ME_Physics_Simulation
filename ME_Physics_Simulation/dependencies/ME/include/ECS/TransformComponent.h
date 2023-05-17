#pragma once

#include "Component.h"
#include "../Helper/Vector2f.h"
#include "../Helper/Angle.h"

namespace ME
{
	class TransformComponent : public Component
	{
	public:

		TransformComponent();
		TransformComponent(unsigned int entityID);

		Vector2f position;
		Angle rotation;
		Vector2f scale;

	};
}



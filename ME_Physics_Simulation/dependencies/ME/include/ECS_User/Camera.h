#pragma once

#include "ComponentRef.h"

namespace ME
{
	class Camera final : public ComponentRef
	{
	public:

		Camera();
		Camera(unsigned int id, ECS* ecs);

	};
}



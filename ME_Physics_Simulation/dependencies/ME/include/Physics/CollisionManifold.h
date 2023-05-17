#pragma once

#include "../Helper/Vector2f.h"

namespace ME
{
	struct CollisionManifold
	{
		Vector2f Normal = Vector2f();
		float Depth = 0;
		bool HasCollision = false;
	};
}

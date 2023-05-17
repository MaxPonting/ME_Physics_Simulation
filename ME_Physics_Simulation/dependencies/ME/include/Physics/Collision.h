#pragma once

#include "CollisionManifold.h"
#include "../ECS/TransformComponent.h"
#include "../ECS/RigidbodyComponent.h"

namespace ME
{
	struct Collision
	{
		CollisionManifold Manifold;
		TransformComponent& TransformA;
		TransformComponent& TransformB;
		RigidbodyComponent* RigidbodyA;
		RigidbodyComponent* RigidbodyB;
	};
}



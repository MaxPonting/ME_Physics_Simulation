#pragma once

#include "Component.h"
#include "../Helper/Vector2f.h"

namespace ME
{
	class TransformComponent;
	class CircleColliderComponent;
	class RectangleColliderComponent;
	class PolygonColliderComponent;
	class CollisionManifold;

	class ColliderComponent : public Component
	{
	public:

		using Component::Component;

		virtual CollisionManifold CheckCollision(const TransformComponent& transform, const ColliderComponent* collider, const TransformComponent& colliderTransform) const = 0;
		virtual CollisionManifold CheckCollision(const TransformComponent& transform, const CircleColliderComponent* circle, const TransformComponent& colliderTransform) const = 0;
		virtual CollisionManifold CheckCollision(const TransformComponent& transform, const RectangleColliderComponent* rectangle, const TransformComponent& colliderTransform) const = 0;
		virtual CollisionManifold CheckCollision(const TransformComponent& transform, const PolygonColliderComponent* polygon, const TransformComponent& colliderTransform) const = 0;
	};
}


#pragma once

#include "ColliderComponent.h"

namespace ME
{
	class CircleColliderComponent final : public ColliderComponent
	{
	public:
		
		using ColliderComponent::ColliderComponent;

		CollisionManifold CheckCollision(const TransformComponent& transform, const ColliderComponent* collider, const TransformComponent& colliderTransform) const override;
		CollisionManifold CheckCollision(const TransformComponent& transform, const CircleColliderComponent* collider, const TransformComponent& colliderTransform) const override;
		CollisionManifold CheckCollision(const TransformComponent& transform, const RectangleColliderComponent* collider, const TransformComponent& colliderTransform) const override;
		CollisionManifold CheckCollision(const TransformComponent& transform, const PolygonColliderComponent* polygon, const TransformComponent& colliderTransform) const override;

		float Radius;
	};
}



#pragma once

#include "ColliderComponent.h"
#include "../Physics/CollisionManifold.h"
#include "../Physics/CollisionAlgo.h"


namespace ME
{
	class RectangleColliderComponent : public ColliderComponent
	{
	public:

		using ColliderComponent::ColliderComponent;

		CollisionManifold CheckCollision(const TransformComponent& transform, const ColliderComponent* collider, const TransformComponent& colliderTransform) const override;
		CollisionManifold CheckCollision(const TransformComponent& transform, const CircleColliderComponent* collider, const TransformComponent& colliderTransform) const override;
		CollisionManifold CheckCollision(const TransformComponent& transform, const RectangleColliderComponent* collider, const TransformComponent& colliderTransform) const override;
		CollisionManifold CheckCollision(const TransformComponent& transform, const PolygonColliderComponent* polygon, const TransformComponent& colliderTransform) const override;

		std::vector<Vector2f> GetVertices(const TransformComponent& transform) const;

		float Width;
		float Height;
	};
}


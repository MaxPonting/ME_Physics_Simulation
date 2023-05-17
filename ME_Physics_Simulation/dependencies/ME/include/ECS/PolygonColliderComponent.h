#pragma once

#include <vector>

#include "ColliderComponent.h"
#include "../Helper/Vector2f.h"
#include "../Helper/Polygon.h"

namespace ME
{
	class PolygonColliderComponent : public ColliderComponent
	{
	public:

		using ColliderComponent::ColliderComponent;
	
		CollisionManifold CheckCollision(const TransformComponent& transform, const ColliderComponent* collider, const TransformComponent& colliderTransform) const override;
		CollisionManifold CheckCollision(const TransformComponent& transform, const CircleColliderComponent* circle, const TransformComponent& colliderTransform) const override;
		CollisionManifold CheckCollision(const TransformComponent& transform, const RectangleColliderComponent* rectangle, const TransformComponent& colliderTransform) const override;
		CollisionManifold CheckCollision(const TransformComponent& transform, const PolygonColliderComponent* polygon, const TransformComponent& colliderTransform) const override;

		std::vector<Vector2f> GetVertices(const TransformComponent& transform) const;
		std::vector<Vector2f> GetRawVertices(const float rotation) const;

		Polygon Polygon;

	};
}


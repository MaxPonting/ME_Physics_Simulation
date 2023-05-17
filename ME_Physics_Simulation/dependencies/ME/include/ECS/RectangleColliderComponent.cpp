#include "RectangleColliderComponent.h"

namespace ME
{
	CollisionManifold RectangleColliderComponent::CheckCollision(const TransformComponent& transform, const ColliderComponent* collider, const TransformComponent& colliderTransform) const
	{
		return collider->CheckCollision(colliderTransform, this, transform);
	}
	CollisionManifold RectangleColliderComponent::CheckCollision(const TransformComponent& transform, const CircleColliderComponent* collider, const TransformComponent& colliderTransform) const
	{
		return GetRectangleCircleCollisionManifold(transform, this, colliderTransform, collider);
	}
	CollisionManifold RectangleColliderComponent::CheckCollision(const TransformComponent& transform, const RectangleColliderComponent* collider, const TransformComponent& colliderTransform) const
	{
		return GetRectangleRectangleCollisionManifold(transform, this, colliderTransform, collider);
	}

	CollisionManifold RectangleColliderComponent::CheckCollision(const TransformComponent& transform, const PolygonColliderComponent* polygon, const TransformComponent& colliderTransform) const
	{
		return GetPolygonRectangleCollisionManifold(colliderTransform, polygon, transform, this);
	}

	std::vector<Vector2f> RectangleColliderComponent::GetVertices(const TransformComponent& transform) const
	{
		std::vector<Vector2f> vertices =
		{
			{  Width / 2,  Height / 2 },
			{  Width / 2, -Height / 2 },
			{ -Width / 2, -Height / 2 },
			{ -Width / 2,  Height / 2 }
		};

		RotateVertices(transform.rotation.getRad(), vertices);

		for (int i = 0; i < vertices.size(); i++)
		{
			vertices[i] += transform.position;
		}	

		return vertices;
	}


}


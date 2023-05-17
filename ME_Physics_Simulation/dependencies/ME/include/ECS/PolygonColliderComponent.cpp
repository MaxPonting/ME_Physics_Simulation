#include "PolygonColliderComponent.h"
#include "../Physics/CollisionManifold.h"
#include "../Physics/CollisionAlgo.h"

namespace ME
{
	CollisionManifold PolygonColliderComponent::CheckCollision(const TransformComponent& transform, const ColliderComponent* collider, const TransformComponent& colliderTransform) const
	{
		return collider->CheckCollision(colliderTransform, this, transform);
	}

	CollisionManifold PolygonColliderComponent::CheckCollision(const TransformComponent& transform, const CircleColliderComponent* circle, const TransformComponent& colliderTransform) const
	{
		return GetPolygonCircleCollisionManifold(transform, this, colliderTransform, circle);
	}

	CollisionManifold PolygonColliderComponent::CheckCollision(const TransformComponent& transform, const RectangleColliderComponent* rectangle, const TransformComponent& colliderTransform) const
	{
		return GetPolygonRectangleCollisionManifold(transform, this, colliderTransform, rectangle);
	}

	CollisionManifold PolygonColliderComponent::CheckCollision(const TransformComponent& transform, const PolygonColliderComponent* polygon, const TransformComponent& colliderTransform) const
	{
		return GetPolygonPolygonCollisionManifold(transform, this, colliderTransform, polygon);
	}

	std::vector<Vector2f> PolygonColliderComponent::GetVertices(const TransformComponent& transform) const
	{
		std::vector<Vector2f> vertices = Polygon.GetVertices();

		RotateVertices(transform.rotation.getRad(), vertices);

		for (int i = 0; i < vertices.size(); i++)
		{
			vertices[i] += transform.position;
		}

		return vertices;
	}

	std::vector<Vector2f> PolygonColliderComponent::GetRawVertices(const float rotation) const
	{
		std::vector<Vector2f> vertices = Polygon.GetVertices();

		RotateVertices(rotation, vertices);

		return vertices;
	}
}

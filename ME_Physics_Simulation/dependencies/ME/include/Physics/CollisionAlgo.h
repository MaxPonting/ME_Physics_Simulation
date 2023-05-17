#pragma once

#include <vector>
#include "../Helper/Vector2f.h"
#include "Collision.h"

namespace ME
{
	class CollisionManifold;
	class ColliderComponent;
	class CircleColliderComponent;
	class RectangleColliderComponent;
	class PolygonColliderComponent;
	class TransformComponent;

	CollisionManifold GetPolygonPolygonCollisionManifold(const TransformComponent& transformA, const PolygonColliderComponent* polyA, const TransformComponent& transformB, const PolygonColliderComponent* polyB);
	CollisionManifold GetPolygonRectangleCollisionManifold(const TransformComponent& transformA, const PolygonColliderComponent* polyA, const TransformComponent& transformB, const RectangleColliderComponent* rectB);
	CollisionManifold GetPolygonCircleCollisionManifold(const TransformComponent& transformA, const PolygonColliderComponent* polyA, const TransformComponent& transformB, const CircleColliderComponent* circleB);
	CollisionManifold GetRectangleCircleCollisionManifold(const TransformComponent& transformA, const RectangleColliderComponent* rectA, const TransformComponent& transformB, const CircleColliderComponent* circleB);
	CollisionManifold GetRectangleRectangleCollisionManifold(const TransformComponent& transformA, const RectangleColliderComponent* rectA, const TransformComponent& transformB, const RectangleColliderComponent* rectB);
	CollisionManifold GetCircleCircleCollisionManifold(const TransformComponent& transformA, const CircleColliderComponent* circleA, const TransformComponent& transformB, const CircleColliderComponent* circleB);

	CollisionManifold AxisAlignedRectangleRectangleCollision(const TransformComponent& transformA, const RectangleColliderComponent* rectA, const TransformComponent& transformB, const RectangleColliderComponent* rectB);
	CollisionManifold AxisAlignedCircleRectangleCollision(const TransformComponent& transformA, const RectangleColliderComponent* rectA, const TransformComponent& transformB, const CircleColliderComponent* circleB);
	CollisionManifold SAT(const TransformComponent& transformA, const std::vector<Vector2f>& verticesA, const TransformComponent& transformB, const std::vector<Vector2f>& verticesB);
	CollisionManifold SATCircle(const TransformComponent& transformA, const std::vector<Vector2f>& verticesA, const TransformComponent& transformB, const CircleColliderComponent* circleB);

	void ProjectVertices(const std::vector<Vector2f>& vertices, const Vector2f& axis, float& min, float& max);
	void ProjectCircle(const Vector2f& center, const float& radius, const Vector2f& axis, float& min, float& max);

	Vector2f FindArithmeticMean(const std::vector<Vector2f>& vertices);

	void RotateVertices(const float rotation, std::vector<Vector2f>& vertices);

	void SolveCollision(Collision collision);
	
}

#include "CircleColliderComponent.h"
#include "../Physics/CollisionManifold.h"
#include "../Physics/CollisionAlgo.h"

namespace ME
{
    CollisionManifold CircleColliderComponent::CheckCollision(const TransformComponent& transform, const ColliderComponent* collider, const TransformComponent& colliderTransform) const
    {
        return collider->CheckCollision(colliderTransform, this, transform);
    }

    CollisionManifold CircleColliderComponent::CheckCollision(const TransformComponent& transform, const CircleColliderComponent* circle, const TransformComponent& colliderTransform) const
    {
        return GetCircleCircleCollisionManifold(transform, this, colliderTransform, circle);
    }

    CollisionManifold CircleColliderComponent::CheckCollision(const TransformComponent& transform, const RectangleColliderComponent* rectangle, const TransformComponent& colliderTransform) const
    {
        return GetRectangleCircleCollisionManifold(colliderTransform, rectangle, transform, this);
    }

    CollisionManifold CircleColliderComponent::CheckCollision(const TransformComponent& transform, const PolygonColliderComponent* polygon, const TransformComponent& colliderTransform) const
    {
        return GetPolygonCircleCollisionManifold(colliderTransform, polygon, transform, this);
    }
    
}


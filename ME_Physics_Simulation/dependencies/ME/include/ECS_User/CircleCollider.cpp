#include "CircleCollider.h"

namespace ME
{
	void CircleCollider::SetRadius(float radius)
	{
		if (p_ECS == nullptr) return;
		CircleColliderComponent*collider = p_ECS->GetComponent<CircleColliderComponent>(m_EntityID);
		if (collider == nullptr) return;
		collider->Radius = radius;
	}

	float CircleCollider::GetRadius()
	{
		if (p_ECS == nullptr) return 0;
		CircleColliderComponent* collider = p_ECS->GetComponent<CircleColliderComponent>(m_EntityID);
		if (collider == nullptr) return 0;
		return collider->Radius;
	}
}
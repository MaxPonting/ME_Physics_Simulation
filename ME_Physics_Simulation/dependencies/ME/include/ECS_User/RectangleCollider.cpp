#include "RectangleCollider.h"

namespace ME
{
	void RectangleCollider::SetWidth(float width)
	{
		if (p_ECS == nullptr) return;
		RectangleColliderComponent* collider = p_ECS->GetComponent<RectangleColliderComponent>(m_EntityID);
		if (collider == nullptr) return;
		collider->Width = width;
	}

	void RectangleCollider::SetHeight(float height)
	{
		if (p_ECS == nullptr) return;
		RectangleColliderComponent* collider = p_ECS->GetComponent<RectangleColliderComponent>(m_EntityID);
		if (collider == nullptr) return;
		collider->Height = height;
	}


	float RectangleCollider::GetWidth()
	{
		if (p_ECS == nullptr) return 0;
		RectangleColliderComponent* collider = p_ECS->GetComponent<RectangleColliderComponent>(m_EntityID);
		if (collider == nullptr) return 0;
		return collider->Width;
	}

	float RectangleCollider::GetHeight()
	{
		if (p_ECS == nullptr) return 0;
		RectangleColliderComponent* collider = p_ECS->GetComponent<RectangleColliderComponent>(m_EntityID);
		if (collider == nullptr) return 0;
		return collider->Height;
	}

}

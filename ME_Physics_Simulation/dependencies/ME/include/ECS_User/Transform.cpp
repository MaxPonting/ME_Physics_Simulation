#include "Transform.h"
#include "../ECS/ECS.h"
#include "../ECS/TransformComponent.h"

namespace ME
{
	Transform::Transform() : ComponentRef() {}
	Transform::Transform(unsigned int entityID, ECS* ecs) : ComponentRef(entityID, ecs) {}

	void Transform::SetPosition(Vector2f position)
	{
		if (p_ECS == nullptr) return;
		TransformComponent* transform = p_ECS->GetComponent<TransformComponent>(m_EntityID);
		if (transform == nullptr) return;
		transform->position = position;
	}

	void Transform::SetRotation(float rotation)
	{
		if (p_ECS == nullptr) return;
		TransformComponent* transform = p_ECS->GetComponent<TransformComponent>(m_EntityID);
		if (transform == nullptr) return;
		transform->rotation = rotation;
	}

	void Transform::SetScale(Vector2f scale)
	{
		if (p_ECS == nullptr) return;
		TransformComponent* transform = p_ECS->GetComponent<TransformComponent>(m_EntityID);
		if (transform == nullptr) return;
		transform->scale = scale;
	}

	Vector2f Transform::GetPosition()
	{
		if (p_ECS == nullptr) return Vector2f();
		TransformComponent* transform = p_ECS->GetComponent<TransformComponent>(m_EntityID);
		if (transform == nullptr) return Vector2f();
		return transform->position;
	}

	float Transform::GetRotation()
	{
		if (p_ECS == nullptr) return 0;
		TransformComponent* transform = p_ECS->GetComponent<TransformComponent>(m_EntityID);
		if (transform == nullptr) return 0;
		return transform->rotation.getDeg();
	}

	Vector2f Transform::GetScale()
	{
		if (p_ECS == nullptr) return Vector2f();
		TransformComponent* transform = p_ECS->GetComponent<TransformComponent>(m_EntityID);
		if (transform == nullptr) return Vector2f();
		return transform->scale;
	}
}

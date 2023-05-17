#include "Rigidbody.h"

ME::Rigidbody::Rigidbody() :
	ComponentRef()
{}

ME::Rigidbody::Rigidbody(unsigned int id, ECS* ecs) :
	ComponentRef(id, ecs)
{}

void ME::Rigidbody::SetStatic(const bool isStatic)
{
	if (p_ECS == nullptr) return;
	RigidbodyComponent* body = p_ECS->GetComponent<RigidbodyComponent>(m_EntityID);
	if (body == nullptr) return;
	body->IsStatic = isStatic;
}

void ME::Rigidbody::AddForce(const Vector2f force)
{
	if (p_ECS == nullptr) return;
	RigidbodyComponent* body = p_ECS->GetComponent<RigidbodyComponent>(m_EntityID);
	if (body == nullptr) return;
	body->AddForce(force);
}

void ME::Rigidbody::AddTorque(const float torque)
{
	if (p_ECS == nullptr) return;
	RigidbodyComponent* body = p_ECS->GetComponent<RigidbodyComponent>(m_EntityID);
	if (body == nullptr) return;
	body->AddTorque(torque);
}

void ME::Rigidbody::SetVelocity(const Vector2f velocity)
{
	if (p_ECS == nullptr) return;
	RigidbodyComponent* body = p_ECS->GetComponent<RigidbodyComponent>(m_EntityID);
	if (body == nullptr) return;
	body->Velocity = velocity;
}

void ME::Rigidbody::SetMass(const float mass)
{
	if (p_ECS == nullptr) return;
	RigidbodyComponent* body = p_ECS->GetComponent<RigidbodyComponent>(m_EntityID);
	if (body == nullptr) return;
	body->Mass = mass;
}

void ME::Rigidbody::SetGravityScale(const float scale)
{
	if (p_ECS == nullptr) return;
	RigidbodyComponent* body = p_ECS->GetComponent<RigidbodyComponent>(m_EntityID);
	if (body == nullptr) return;
	body->GravityScale = scale;
}

void ME::Rigidbody::SetRestitution(const float res)
{
	if (p_ECS == nullptr) return;
	RigidbodyComponent* body = p_ECS->GetComponent<RigidbodyComponent>(m_EntityID);
	if (body == nullptr) return;
	body->SetRestitution(res);
}

bool ME::Rigidbody::GetStatic()
{
	if (p_ECS == nullptr) return false;
	RigidbodyComponent* body = p_ECS->GetComponent<RigidbodyComponent>(m_EntityID);
	if (body == nullptr) return false;
	return body->IsStatic;
}

float ME::Rigidbody::GetMass()
{
	if (p_ECS == nullptr) return 0;
	RigidbodyComponent* body = p_ECS->GetComponent<RigidbodyComponent>(m_EntityID);
	if (body == nullptr) return 0;
	return body->Mass;
}

ME::Vector2f ME::Rigidbody::GetVelocity()
{
	if (p_ECS == nullptr) return Vector2f();
	RigidbodyComponent* body = p_ECS->GetComponent<RigidbodyComponent>(m_EntityID);
	if (body == nullptr) return Vector2f();
	return body->Velocity;
}

float ME::Rigidbody::GetGravityScale()
{
	if (p_ECS == nullptr) return 0;
	RigidbodyComponent* body = p_ECS->GetComponent<RigidbodyComponent>(m_EntityID);
	if (body == nullptr) return 0;
	return body->GravityScale;
}

float ME::Rigidbody::GetRestitution()
{
	if (p_ECS == nullptr) return 0;
	RigidbodyComponent* body = p_ECS->GetComponent<RigidbodyComponent>(m_EntityID);
	if (body == nullptr) return 0;
	return body->GetRestitution();
}

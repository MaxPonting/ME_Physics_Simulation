#include "RigidbodyComponent.h"
#include "TransformComponent.h"

namespace ME
{
	RigidbodyComponent::RigidbodyComponent() :
		Component(),
		IsStatic(false),
		Mass(1),
		GravityScale(0),
		Force(Vector2f()),
		Velocity(Vector2f()),
		Torque(0),
		RotationalVelocity(0),
		m_Restitution(1)
	{}

	RigidbodyComponent::RigidbodyComponent(unsigned int entityID) :
		Component(entityID),
		IsStatic(false),
		Mass(1),
		GravityScale(0),
		Force(Vector2f()),
		Velocity(Vector2f()),
		Torque(0),
		RotationalVelocity(0),
		m_Restitution(1)
	{}

	void RigidbodyComponent::AddForce(Vector2f force)
	{
		Force += force;
	}

	void RigidbodyComponent::AddTorque(float torque)
	{
		Torque += torque;
	}

	void RigidbodyComponent::SetRestitution(float res)
	{
		m_Restitution = res;

		if (m_Restitution > 1) m_Restitution = 1;
		else if (m_Restitution < 0) m_Restitution = 0;
	}

	float RigidbodyComponent::GetRestitution()
	{
		return m_Restitution;
	}

	void RigidbodyComponent::Update(TransformComponent& transform, float deltaTime)
	{
		if (IsStatic) return;

		ApplyGravity(deltaTime);
		ApplyForce(deltaTime);
		ApplyTorque(deltaTime);
		Step(transform, deltaTime);
	}

	void RigidbodyComponent::ApplyGravity(float deltaTime)
	{
		Force += GRAVITY * Mass * GravityScale * deltaTime;
	}

	void RigidbodyComponent::ApplyForce(float deltaTime)
	{
		Velocity += Force / Mass;
	}

	void RigidbodyComponent::ApplyTorque(float deltaTime)
	{
		RotationalVelocity += Torque / Mass;
	}

	void RigidbodyComponent::Step(TransformComponent& transform, float deltaTime)
	{
		transform.position += Velocity * deltaTime;
		transform.rotation += RotationalVelocity * deltaTime;	
		Force = Vector2f();
		Torque = 0;
	}

}
#pragma once

#include "Component.h"
#include "../Helper/Vector2f.h"

#define GRAVITY ME::Vector2f(0, -9.81)

namespace ME
{
	class TransformComponent;
	class RigidbodyComponent : public Component
	{
	public:

		RigidbodyComponent();
		RigidbodyComponent(unsigned int entityID);
		
		void AddForce(Vector2f force);
		void AddTorque(float torque);

		void SetRestitution(float res);

		float GetRestitution();

		void Update(TransformComponent& transform, float deltaTime);
		
		bool IsStatic;
		float Mass;
		float GravityScale;
		float Torque;
		float RotationalVelocity;
		
		Vector2f Force;
		Vector2f Velocity;

	private:

		void ApplyGravity(float deltaTime);
		void ApplyForce(float deltaTime);
		void ApplyTorque(float deltaTime);
		void Step(TransformComponent& transform, float deltaTime);

		float m_Restitution;
	};
}
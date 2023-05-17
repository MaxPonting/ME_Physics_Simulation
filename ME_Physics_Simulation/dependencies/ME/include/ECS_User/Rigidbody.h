#pragma once

#include "ComponentRef.h"
#include "../Helper/Vector2f.h"

namespace ME
{
	class Rigidbody : public ComponentRef
	{
	public:

		Rigidbody();
		Rigidbody(unsigned int id, ECS* ecs);

		void SetStatic(const bool isStatic);
		void AddForce(const Vector2f force);
		void AddTorque(const float torque);
		void SetVelocity(const Vector2f velocity);
		void SetMass(const float mass);
		void SetGravityScale(const float scale);
		void SetRestitution(const float res);

		bool GetStatic();
		float GetMass();
		Vector2f GetVelocity();
		float GetGravityScale();
		float GetRestitution();
	};
}



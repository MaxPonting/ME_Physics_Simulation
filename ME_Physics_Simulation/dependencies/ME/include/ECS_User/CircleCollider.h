#pragma once

#include "Collider.h"

namespace ME
{
	class CircleCollider : public Collider
	{
	public:

		using Collider::Collider;

		void SetRadius(float radius);

		float GetRadius();
	};
}



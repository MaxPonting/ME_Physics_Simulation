#pragma once

#include "Collider.h"

namespace ME
{
	class RectangleCollider : public Collider
	{
	public:

		using Collider::Collider;

		void SetWidth(float width);
		void SetHeight(float height);

		float GetWidth();
		float GetHeight();

	};
}



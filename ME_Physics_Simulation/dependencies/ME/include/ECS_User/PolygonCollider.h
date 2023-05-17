#pragma once

#include <vector>

#include "Collider.h"
#include "../Helper/Polygon.h"

namespace ME
{
	class PolygonCollider : public Collider
	{
	public:

		using Collider::Collider;

		void SetPolygon(Polygon polygon);

		Polygon GetPolygon();

	};
}



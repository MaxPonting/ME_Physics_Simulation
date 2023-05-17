#include "PolygonCollider.h"

namespace ME
{
	void PolygonCollider::SetPolygon(Polygon polygon)
	{
		if (p_ECS == nullptr) return;
		PolygonColliderComponent* collider = p_ECS->GetComponent<PolygonColliderComponent>(m_EntityID);
		if (collider == nullptr) return;
		collider->Polygon = polygon;
	}

	Polygon PolygonCollider::GetPolygon()
	{
		if (p_ECS == nullptr) return std::vector<Vector2f>();
		PolygonColliderComponent* collider = p_ECS->GetComponent<PolygonColliderComponent>(m_EntityID);
		if (collider == nullptr) return std::vector<Vector2f>();
		return collider->Polygon;
	}

}

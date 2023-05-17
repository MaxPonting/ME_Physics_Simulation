#include "PolygonRenderer.h"
#include "../ECS/ECS.h"
#include "../ECS/PolygonRendererComponent.h"

namespace ME
{
	PolygonRenderer::PolygonRenderer() : ComponentRef() {}
	PolygonRenderer::PolygonRenderer(unsigned int id, ECS* ecs) : ComponentRef(id, ecs) {}

	void PolygonRenderer::SetPolygon(Polygon polygon)
	{
		if (p_ECS == nullptr) return;
		PolygonRendererComponent* renderer = p_ECS->GetComponent<PolygonRendererComponent>(m_EntityID);
		if (renderer == nullptr) return;
		renderer->SetPolygon(polygon);
	}

	void PolygonRenderer::SetColour(RGBA colour)
	{
		if (p_ECS == nullptr) return;
		PolygonRendererComponent* renderer = p_ECS->GetComponent<PolygonRendererComponent>(m_EntityID);
		if (renderer == nullptr) return;
		renderer->colour = colour;
	}

	void PolygonRenderer::SetLayer(int layer)
	{
		if (p_ECS == nullptr) return;
		PolygonRendererComponent* renderer = p_ECS->GetComponent<PolygonRendererComponent>(m_EntityID);
		if (renderer == nullptr) return;
		renderer->layer = layer;
	}

	Polygon PolygonRenderer::GetPolygon(Polygon polygon)
	{
		if (p_ECS == nullptr) return Polygon();
		PolygonRendererComponent* renderer = p_ECS->GetComponent<PolygonRendererComponent>(m_EntityID);
		if (renderer == nullptr) return Polygon();
		renderer->GetPolygon();
	}

	RGBA PolygonRenderer::GetColour()
	{
		if (p_ECS == nullptr) return RGBA();
		PolygonRendererComponent* renderer = p_ECS->GetComponent<PolygonRendererComponent>(m_EntityID);
		if (renderer == nullptr) return RGBA();
		return renderer->colour;
	}

	int PolygonRenderer::GetLayer()
	{
		if (p_ECS == nullptr) return 0;
		PolygonRendererComponent* renderer = p_ECS->GetComponent<PolygonRendererComponent>(m_EntityID);
		if (renderer == nullptr) return 0;
		return renderer->layer;
	}
}

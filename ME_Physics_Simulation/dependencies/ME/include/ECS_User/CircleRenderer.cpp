#include "CircleRenderer.h"
#include "../ECS/ECS.h"
#include "../ECS/CircleRendererComponent.h"

namespace ME
{
	CircleRenderer::CircleRenderer() : ComponentRef() {}
	CircleRenderer::CircleRenderer(unsigned int id, ECS* ecs) : ComponentRef(id, ecs) {}

	void CircleRenderer::SetRadius(unsigned int radius)
	{
		if (p_ECS == nullptr) return;
		CircleRendererComponent* renderer = p_ECS->GetComponent<CircleRendererComponent>(m_EntityID);
		if (renderer == nullptr) return;
		renderer->SetRadius(radius);
	}

	void CircleRenderer::SetColour(RGBA colour)
	{
		if (p_ECS == nullptr) return;
		CircleRendererComponent* renderer = p_ECS->GetComponent<CircleRendererComponent>(m_EntityID);
		if (renderer == nullptr) return;
		renderer->colour = colour;
	}

	void CircleRenderer::SetLayer(int layer)
	{
		if (p_ECS == nullptr) return;
		CircleRendererComponent* renderer = p_ECS->GetComponent<CircleRendererComponent>(m_EntityID);
		if (renderer == nullptr) return;
		renderer->layer = layer;
	}

	unsigned int CircleRenderer::GetRadius()
	{
		if (p_ECS == nullptr) return 0;
		CircleRendererComponent* renderer = p_ECS->GetComponent<CircleRendererComponent>(m_EntityID);
		if (renderer == nullptr) return 0;
		return renderer->GetRadius();
	}

	RGBA CircleRenderer::GetColour()
	{
		if (p_ECS == nullptr) return RGBA();
		CircleRendererComponent* renderer = p_ECS->GetComponent<CircleRendererComponent>(m_EntityID);
		if (renderer == nullptr) return RGBA();
		return renderer->colour;
	}

	int CircleRenderer::GetLayer()
	{
		if (p_ECS == nullptr) return 0;
		CircleRendererComponent* renderer = p_ECS->GetComponent<CircleRendererComponent>(m_EntityID);
		if (renderer == nullptr) return 0;
		return renderer->layer;
	}
}





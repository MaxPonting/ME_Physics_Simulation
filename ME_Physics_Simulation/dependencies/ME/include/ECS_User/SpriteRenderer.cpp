#include "SpriteRenderer.h"
#include "../ECS/ECS.h"
#include "../ECS/SpriteRendererComponent.h"

namespace ME
{
	SpriteRenderer::SpriteRenderer() : ComponentRef() {}
	SpriteRenderer::SpriteRenderer(unsigned int id, ECS* ecs) : ComponentRef(id, ecs) {}

	void SpriteRenderer::SetTexture(Texture texture)
	{
		if (p_ECS == nullptr) return;
		SpriteRendererComponent* renderer = p_ECS->GetComponent<SpriteRendererComponent>(m_EntityID);
		if (renderer == nullptr) return;
		renderer->texture = texture;
	}

	void SpriteRenderer::SetColour(RGBA colour)
	{
		if (p_ECS == nullptr) return;
		SpriteRendererComponent* renderer = p_ECS->GetComponent<SpriteRendererComponent>(m_EntityID);
		if (renderer == nullptr) return;
		renderer->colour = colour;
	}

	void SpriteRenderer::SetLayer(int layer)
	{
		if (p_ECS == nullptr) return;
		SpriteRendererComponent* renderer = p_ECS->GetComponent<SpriteRendererComponent>(m_EntityID);
		if (renderer == nullptr) return;
		renderer->layer = layer;
	}

	Texture SpriteRenderer::GetTexture()
	{
		if (p_ECS == nullptr) return Texture();
		SpriteRendererComponent* renderer = p_ECS->GetComponent<SpriteRendererComponent>(m_EntityID);
		if (renderer == nullptr) return Texture();
		return renderer->texture;
	}

	RGBA SpriteRenderer::GetColour()
	{
		if (p_ECS == nullptr) return RGBA();
		SpriteRendererComponent* renderer = p_ECS->GetComponent<SpriteRendererComponent>(m_EntityID);
		if (renderer == nullptr) return RGBA();
		return renderer->colour;
	}

	int SpriteRenderer::GetLayer()
	{
		if (p_ECS == nullptr) return 0;
		SpriteRendererComponent* renderer = p_ECS->GetComponent<SpriteRendererComponent>(m_EntityID);
		if (renderer == nullptr) return 0;
		return renderer->layer;
	}
}

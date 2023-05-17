#include "TextRenderer.h"
#include "../ECS/ECS.h"
#include "../ECS/TextRendererComponent.h"

namespace ME
{
	TextRenderer::TextRenderer() : ComponentRef() {}
	TextRenderer::TextRenderer(unsigned int id, ECS* ecs) : ComponentRef(id, ecs) {}

	void TextRenderer::SetText(std::string text)
	{
		if (p_ECS == nullptr) return;
		TextRendererComponent* renderer = p_ECS->GetComponent<TextRendererComponent>(m_EntityID);
		if (renderer == nullptr) return;
		renderer->SetText(text);
	}

	void TextRenderer::SetFont(Font font)
	{
		if (p_ECS == nullptr) return;
		TextRendererComponent* renderer = p_ECS->GetComponent<TextRendererComponent>(m_EntityID);
		if (renderer == nullptr) return;
		renderer->font = font;
	}

	void TextRenderer::SetFontSize(unsigned int size)
	{
		if (p_ECS == nullptr) return;
		TextRendererComponent* renderer = p_ECS->GetComponent<TextRendererComponent>(m_EntityID);
		if (renderer == nullptr) return;
		renderer->SetFontSize(size);
	}

	void TextRenderer::SetColour(RGBA colour)
	{
		if (p_ECS == nullptr) return;
		TextRendererComponent* renderer = p_ECS->GetComponent<TextRendererComponent>(m_EntityID);
		if (renderer == nullptr) return;
		renderer->colour = colour;
	}

	void TextRenderer::SetLayer(int layer)
	{
		if (p_ECS == nullptr) return;
		TextRendererComponent* renderer = p_ECS->GetComponent<TextRendererComponent>(m_EntityID);
		if (renderer == nullptr) return;
		renderer->layer = layer;
	}

	std::string TextRenderer::GetText()
	{
		if (p_ECS == nullptr) return std::string();
		TextRendererComponent* renderer = p_ECS->GetComponent<TextRendererComponent>(m_EntityID);
		if (renderer == nullptr) return std::string();
		return renderer->GetText();
	}

	Font TextRenderer::GetFont()
	{
		if (p_ECS == nullptr) return Font();
		TextRendererComponent* renderer = p_ECS->GetComponent<TextRendererComponent>(m_EntityID);
		if (renderer == nullptr) return Font();
		return renderer->font;
	}

	unsigned int TextRenderer::GetTextSize()
	{
		if (p_ECS == nullptr) return 0;
		TextRendererComponent* renderer = p_ECS->GetComponent<TextRendererComponent>(m_EntityID);
		if (renderer == nullptr) return 0;
		return renderer->GetFontSize();
	}

	RGBA TextRenderer::GetColour()
	{
		if (p_ECS == nullptr) return RGBA();
		TextRendererComponent* renderer = p_ECS->GetComponent<TextRendererComponent>(m_EntityID);
		if (renderer == nullptr) return RGBA();
		return renderer->colour;
	}

	int TextRenderer::GetLayer()
	{
		if (p_ECS == nullptr) return 0;
		TextRendererComponent* renderer = p_ECS->GetComponent<TextRendererComponent>(m_EntityID);
		if (renderer == nullptr) return 0;
		return renderer->layer;
	}
}

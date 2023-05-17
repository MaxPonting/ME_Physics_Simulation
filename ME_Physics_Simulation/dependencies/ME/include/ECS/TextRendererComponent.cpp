#include "TextRendererComponent.h"
#include "../Engine/Engine.h"

namespace ME
{
	TextRendererComponent::TextRendererComponent() :
		Component(),
		layer(0),
		m_FontSize(0),
		p_SDLFont(nullptr),
		p_SDLTexture(nullptr),
		m_Text("")
	{
		m_NewFontNeeded = true;
		m_NewTextureNeeded = true;
	}

	TextRendererComponent::TextRendererComponent(unsigned int entityID) :
		Component(entityID),
		layer(0),
		m_FontSize(12),
		p_SDLFont(nullptr),
		p_SDLTexture(nullptr),
		m_Text("")
	{
		m_NewFontNeeded = true;
		m_NewTextureNeeded = true;
	}

	void TextRendererComponent::CreateSDLTexture(const Renderer& renderer, const char* filePath)
	{
		if (!m_NewTextureNeeded) return;

		m_NewTextureNeeded = false;

		if (p_SDLTexture != nullptr) SDLCall(SDL_DestroyTexture(p_SDLTexture));
	
		if (m_NewFontNeeded)
		{
			if (p_SDLFont != nullptr) SDLCall(TTF_CloseFont(p_SDLFont));
			SDLCall(p_SDLFont = TTF_OpenFont(filePath, m_FontSize));
			m_NewFontNeeded = false;
		}

		const char* text = m_Text.c_str();

		SDLCall(SDL_Surface * surface = TTF_RenderText_Blended(
			p_SDLFont,
			text,
			{ colour.GetR(), colour.GetG(), colour.GetB(), colour.GetA() }
		));

		m_TextureSize = { surface->w, surface->h };

		p_SDLTexture = renderer.CreateTextureFromSurface(surface);

		SDLCall(SDL_FreeSurface(surface));
	}

	void TextRendererComponent::SetFontSize(unsigned int size)
	{
		m_FontSize = size;
		m_NewFontNeeded = true;
		m_NewTextureNeeded = true;
	}

	void TextRendererComponent::SetText(std::string text)
	{
		m_Text = text;
		m_NewTextureNeeded = true;
	}

	SDL_Texture* TextRendererComponent::GetSDLTexture()
	{
		return p_SDLTexture;
	}

	Vector2i TextRendererComponent::GetTextureSize()
	{
		return m_TextureSize;
	}

	unsigned int TextRendererComponent::GetFontSize()
	{
		return m_FontSize;
	}

	std::string TextRendererComponent::GetText()
	{
		return m_Text;
	}

	
}


#pragma once

#include <SDL.h>
#include <SDL_ttf.h>

#include "Component.h"
#include "../User/Font.h"
#include "../Rendering/Renderer.h"
#include "../Helper/RGBA.h"

namespace ME
{
	class TextRendererComponent : public Component
	{
	public:

		TextRendererComponent();
		TextRendererComponent(unsigned int entityID);

		void CreateSDLTexture(const Renderer& renderer, const char* filePath);

		void SetFontSize(unsigned int size);
		void SetText(std::string text);

		SDL_Texture* GetSDLTexture();
		Vector2i GetTextureSize();
		unsigned int GetFontSize();
		std::string GetText();
				
		Font font;
		RGBA colour;
		int layer;

	private:

		TTF_Font* p_SDLFont;
		SDL_Texture* p_SDLTexture;
		unsigned int m_FontSize;
		Vector2i m_TextureSize;
		std::string m_Text;
		bool m_NewFontNeeded;
		bool m_NewTextureNeeded;

	};
}



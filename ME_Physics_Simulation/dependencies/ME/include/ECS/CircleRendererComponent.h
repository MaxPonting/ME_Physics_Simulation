#pragma once

#include "Component.h"
#include "../Rendering/TextureContainer.h"

namespace ME
{
	class CircleRendererComponent final : public Component
	{
	public:

		CircleRendererComponent();
		CircleRendererComponent(unsigned int entityID);

		void SetRadius(float radius);
		void CreateSDLTexture(const Renderer& renderer);
		
		unsigned int GetRadius();
		SDL_Texture* GetSDLTexture();

		RGBA colour;
		int layer;

	private:
		
		unsigned int m_Radius;
		bool m_NewTextureNeeded;
		SDL_Texture* p_SDLTexture;

	};
}



#pragma once

#include "Component.h"
#include "../Rendering/TextureContainer.h"
#include "../Helper/Polygon.h"

namespace ME
{
	class PolygonRendererComponent final : public Component
	{
	public:

		PolygonRendererComponent();
		PolygonRendererComponent(unsigned int entityID);

		void SetPolygon(Polygon polygon);
		void CreateSDLTexture(const Renderer& renderer);
	
		Polygon GetPolygon();
		SDL_Texture* GetSDLTexture();
		Vector2i GetOffset();
		
		RGBA colour;
		int layer;

	private:

		Polygon m_Polygon;
		bool m_NewTextureNeeded;
		SDL_Texture* p_SDLTexture;
		Vector2i m_Offset;

	};

}


#include "CircleRendererComponent.h"
#include "../Engine/Engine.h"

namespace ME
{
	CircleRendererComponent::CircleRendererComponent() :
		Component(),
		layer(0),
		m_Radius(0),
		p_SDLTexture(nullptr),
		m_NewTextureNeeded(false)
	{}

	CircleRendererComponent::CircleRendererComponent(unsigned int entityID) :
		Component(entityID),
		layer(0),
		m_Radius(1),
		p_SDLTexture(nullptr),
		m_NewTextureNeeded(true)
	{}

	void CircleRendererComponent::SetRadius(float radius)
	{
		m_Radius = radius;
		m_NewTextureNeeded = true;
	}

	void CircleRendererComponent::CreateSDLTexture(const Renderer& renderer)
	{
		if (m_Radius == 0) return;

		if (!m_NewTextureNeeded) return;
		
		m_NewTextureNeeded = false;

		if (p_SDLTexture != nullptr)
		{
			SDLCall(SDL_DestroyTexture(p_SDLTexture));
		}

		SDLCall(SDL_Surface * surface = SDL_CreateRGBSurfaceWithFormat(0, m_Radius * 2, m_Radius * 2, 32, SDL_PIXELFORMAT_RGBA32));
		Uint32* buffer = (Uint32*)surface->pixels;

		int radius2 = m_Radius * m_Radius;
		int row = 0;
		int column = 0;
		int offset;
		Uint32 colour;
		SDLCall(colour = SDL_MapRGBA(surface->format, 255, 255, 255, 255));
		SDLCall(SDL_LockSurface(surface));

		while (row < surface->w)
		{
			column = 0;
			while (column < surface->h)
			{
				int dx = m_Radius - row;
				int dy = m_Radius - column;
				if (dx * dx + dy * dy < radius2)
				{
					offset = row * surface->h + column;
					buffer[offset] = colour;
				}
				column++;
			}
			row++;
		}
		SDLCall(SDL_UnlockSurface(surface));

		p_SDLTexture = renderer.CreateTextureFromSurface(surface);
		SDLCall(SDL_FreeSurface(surface));
	}

	SDL_Texture* CircleRendererComponent::GetSDLTexture()
	{
		return p_SDLTexture;
	}

	unsigned int CircleRendererComponent::GetRadius()
	{
		return m_Radius;
	}
}

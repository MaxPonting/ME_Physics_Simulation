#pragma once

/* SDL2 */
#include "SDL.h"

/* ME */
#include "../Helper/RGBA.h"
#include "../Helper/Vector2i.h"
#include "../User/Texture.h"


namespace ME
{
	//
	// Own an texture, colour and size.
	// Used to render a texture to a window.
	//
	class Sprite final
	{
	public:

		/* CONSTRUCTORS */
		Sprite();
		Sprite(SDL_Texture* texture, const RGBA colour, const Vector2i size);

		/* GETTERS */
		SDL_Texture* GetTexture() const ;
		
		/* PUBLIC MEMBERS */
		RGBA colour;
		Vector2i size;

	private:

		/* PRIVATE MEMBERS */
		SDL_Texture* m_Texture;
		
	};
}



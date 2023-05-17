#pragma once

/* C++ */
#include <vector>

/* SDL2 */
#include <SDL.h>
#include <SDL_image.h>

/* ME */
#include "Sprite.h"
#include "../ECS/TransformComponent.h"
#include "ObjectToRender.h"
#include "../Engine/Window.h"
#include "../Helper/SDLWrapper.h"

namespace ME
{
	//
	// Owns SDL2 renderer.
	// Renders sprites to the SDL2 Window at a given transform.
	//
	class Renderer final : public SDLWrapper 
	{
	public:

		Renderer();
		Renderer(const Window window);
		
		void Clear();
		void Present(const Window windowa);

		void Enqueue(ObjectToRender object);
		void RenderQueue(const Window window, const TransformComponent mainCamera);

		void RenderSprite(const Sprite sprite, const Vector2f position) const;
		
		void SDLCleanUp();

		void SetRenderTargetToTexture(SDL_Texture* texture) const;
		void ResetRenderTarget() const;
		void SetRenderDrawColor(RGBA color) const;
		void RenderDrawPoint(int x, int y) const;

		SDL_Texture* CreateTexture(SDL_TextureAccess access, int w, int h) const;
		SDL_Texture* CreateTextureFromSurface(SDL_Surface* surface) const;
		SDL_Texture* CreateTextureFromFilePath(const char* filePath) const;

		Vector2f GetWindowPointRelativeToCamera(const TransformComponent mainCamera, Vector2f point);

		SDL_RendererInfo GetInfo();

	private:
		
		void RenderObject(const Window window, const ObjectToRender object, const TransformComponent mainCamera);
		void SetRendererSize();
		SDL_FRect GetRectRelativeToCamera(const TransformComponent mainCamera, SDL_FRect rect);
		bool IsRectInsideCamera(const SDL_FRect& rect, const TransformComponent& camera);
		
		SDL_Renderer* p_Renderer;
		SDL_RendererInfo m_Info;
		Vector2i m_RendererSize;
		std::vector<ObjectToRender> m_ObjectsToRender;
	};
}



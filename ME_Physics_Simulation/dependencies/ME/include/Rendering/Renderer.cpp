/* C++ */
#include <algorithm>

/* ME */
#include "Renderer.h"
#include "../Engine/Engine.h"

namespace ME
{
	//
	// Default Constructor
	//
	Renderer::Renderer() :
		p_Renderer(nullptr),
		m_Info(SDL_RendererInfo())		
	{}

	//
	// Creates a SDL Renderer.
	// Sets the logical size of the renderer.
	//
	Renderer::Renderer(const Window window)
	{		
		//SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl");
		SDLCall(SDL_SetHint(SDL_HINT_RENDER_BATCHING, "1"));
		SDLCall(p_Renderer = SDL_CreateRenderer(window.GetWindow(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC));
		SDLCall(SDL_RenderSetLogicalSize(p_Renderer, window.GetSize().X, window.GetSize().Y));
		SDLCall(SDL_GetRendererInfo(p_Renderer, &m_Info));
	}

	//
	// Clears the renderer
	//
	void Renderer::Clear()
	{
		SDLCall(SDL_RenderClear(p_Renderer));
	}

	//
	// Presents the renderer to the window
	//
	void Renderer::Present(const Window window)
	{
		SDLCall(SDL_SetRenderDrawColor(
			p_Renderer,
			window.m_Colour.GetR(),
			window.m_Colour.GetG(),
			window.m_Colour.GetB(),
			window.m_Colour.GetA()
		));
		SDLCall(SDL_RenderPresent(p_Renderer));
	}

	//
	// Queues an object to render
	//
	void Renderer::Enqueue(ObjectToRender object)
	{
		m_ObjectsToRender.emplace_back(object);
	}

	//
	// Sorts the queued objects in increasing order by layer then renders them.
	//
	void Renderer::RenderQueue(const Window window, const TransformComponent mainCamera)
	{
		std::sort(m_ObjectsToRender.begin(), m_ObjectsToRender.end(),
			[](const ObjectToRender& o1, const ObjectToRender& o2) { return o1.layer < o2.layer; });

		SetRendererSize();

		for (int i = 0; i < m_ObjectsToRender.size(); i++)
		{
			RenderObject(window, m_ObjectsToRender[i], mainCamera);
		}

		m_ObjectsToRender.clear();
	}

	//
	// Renders an object relative to the main camera
	//
	void Renderer::RenderObject(const Window window, const ObjectToRender object, const TransformComponent mainCamera)
	{
		if (object.sprite.GetTexture() == nullptr) return;
		if (mainCamera.scale.X == 0 || mainCamera.scale.Y == 0) return;

		//
		// Set rect
		//
		SDL_FRect rect = SDL_FRect();
		rect.x = object.transform.position.X;
		rect.y = object.transform.position.Y;
		rect.w = object.sprite.size.X * object.transform.scale.X;
		rect.h = object.sprite.size.Y * object.transform.scale.Y;

		//
		// Check if rect is inside camera
		//
		if (!IsRectInsideCamera(rect, mainCamera)) return;

		//
		// Set relative to main camera
		//
		rect = GetRectRelativeToCamera(mainCamera, rect);

		SDLCall(

			SDL_SetTextureColorMod
			(
				object.sprite.GetTexture(),
				object.sprite.colour.GetR(),
				object.sprite.colour.GetG(),
				object.sprite.colour.GetB()
			);

		SDL_SetTextureAlphaMod
		(
			object.sprite.GetTexture(),
			object.sprite.colour.GetA()
		);


		SDL_RenderCopyExF
		(
			p_Renderer,
			object.sprite.GetTexture(),
			NULL,
			&rect,
			-(object.transform.rotation.getDeg() - mainCamera.rotation.getDeg()),
			NULL,
			SDL_FLIP_NONE
		));
	}

	//
	// Renders a sprite to the screen.
	// The sprite will not be rendered relative to the main camera.
	//
	void Renderer::RenderSprite(const Sprite sprite, const Vector2f position) const
	{
		if (sprite.GetTexture() == nullptr) return;

		SDLCall(

		SDL_SetTextureColorMod
		(
			sprite.GetTexture(),
			sprite.colour.GetR(),
			sprite.colour.GetG(),
			sprite.colour.GetB()
		);

		SDL_SetTextureAlphaMod
		(
			sprite.GetTexture(),
			sprite.colour.GetA()
		);

		SDL_FRect rect;
		rect.x = position.X;
		rect.y = position.Y;
		rect.w = sprite.size.X;
		rect.h = sprite.size.Y;
		SDL_RenderCopyF
		(
			p_Renderer,
			sprite.GetTexture(),
			NULL,
			&rect
		));
	}

	//
	// Checks the size of the SDL renderer and stores the result
	//
	void Renderer::SetRendererSize()
	{
		int w, h;
		SDLCall(SDL_RenderGetLogicalSize(p_Renderer, &w, &h));
		m_RendererSize = { w, h };
	}

	//
	// Returns a SDL_FRect relative to a camera
	//
	SDL_FRect Renderer::GetRectRelativeToCamera(const TransformComponent mainCamera, SDL_FRect rect)
	{
		//
		// Invert Y
		// 
		rect.y = -rect.y;

		//
		// Set position relative to camera scale
		//	
		rect.x /= mainCamera.scale.X;
		rect.y /= mainCamera.scale.Y;

		//
		// Set position relative to camera position
		//
		rect.x -= mainCamera.position.X / mainCamera.scale.X;
		rect.y += mainCamera.position.Y / mainCamera.scale.Y;

		//
		// Center rect position
		//
		rect.x -= rect.w / 2;
		rect.y -= rect.h / 2;
		rect.x += m_RendererSize.X / 2;
		rect.y += m_RendererSize.Y / 2;

		//
		// Set scale relative to camera scale
		//
		float changeX = (rect.w / mainCamera.scale.X) - rect.w;
		float changeY = (rect.h / mainCamera.scale.Y) - rect.h;
		rect.w += changeX;
		rect.h += changeY;
		rect.x -= changeX / 2;
		rect.y -= changeY / 2;

		//
		// ADD CAMERA ROTATION!!!
		//

		return rect;
	}

	//
	// Checks if a rect is inside a camera
	//
	bool Renderer::IsRectInsideCamera(const SDL_FRect& rect, const TransformComponent& camera)
	{
		Vector2f cameraSize = { m_RendererSize.X * camera.scale.X, m_RendererSize.Y * camera.scale.Y };

		if (abs(rect.x - camera.position.X) > rect.w + cameraSize.X) return false;
		if (abs(rect.y - camera.position.Y) > rect.h + cameraSize.Y) return false;

		return true;
	}

	Vector2f Renderer::GetWindowPointRelativeToCamera(const TransformComponent mainCamera, Vector2f point)
	{
		//point = { 0, 0 };

		point.Y = -point.Y;

		point.X *= mainCamera.scale.X;
		point.Y *= mainCamera.scale.Y;

		point.X += mainCamera.position.X;
		point.Y += mainCamera.position.Y;

		point.X -= m_RendererSize.X / 2 * mainCamera.scale.X;
		point.Y += m_RendererSize.Y / 2 * mainCamera.scale.Y;

		return point;
	}

	

	//
	// Destroys the SDL Renderer
	//
	void Renderer::SDLCleanUp()
	{
		SDLCall(SDL_DestroyRenderer(p_Renderer));
	}

	//
	// Sets the render target to a texture
	//
	void Renderer::SetRenderTargetToTexture(SDL_Texture* texture) const
	{
		SDLCall(SDL_SetRenderTarget(p_Renderer, texture));
	}

	//
	// Sets the render target to the window
	// 
	void Renderer::ResetRenderTarget() const
	{
		SDLCall(SDL_SetRenderTarget(p_Renderer, 0));
	}

	//
	// Sets the rendering colour.
	// Does not affect textures.
	//
	void Renderer::SetRenderDrawColor(RGBA color) const
	{
		SDLCall(SDL_SetRenderDrawColor(p_Renderer, color.GetR(), color.GetG(), color.GetB(), color.GetA()));
	}

	//
	// Draws a point on the window
	//
	void Renderer::RenderDrawPoint(int x, int y) const
	{
		SDLCall(SDL_RenderDrawPoint(p_Renderer, x, y));
	}

	//
	// Returns a RGBA32 SDL texture
	//
	SDL_Texture* Renderer::CreateTexture(SDL_TextureAccess access, int w, int h) const
	{
		SDLCall(SDL_Texture * texture = SDL_CreateTexture(p_Renderer, SDL_PIXELFORMAT_RGBA32, access, w, h));
		return texture;
	}

	//
	// Returns a SDL Texture from a given SDL surface
	//
	SDL_Texture* Renderer::CreateTextureFromSurface(SDL_Surface* surface) const
	{
		SDLCall(SDL_Texture* texture = SDL_CreateTextureFromSurface(p_Renderer, surface));
		return texture;
	}

	//
	// Returns a SDL texture from a file path
	//
	SDL_Texture* Renderer::CreateTextureFromFilePath(const char* filePath) const
	{
		return SDLCall(IMG_LoadTexture(p_Renderer, filePath));
	}

	//
	// Returns the SDL_RendererInfo of the renderer
	//
	SDL_RendererInfo Renderer::GetInfo()
	{
		return m_Info;
	}

	
}

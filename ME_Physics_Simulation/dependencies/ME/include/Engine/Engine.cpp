#include "Engine.h"
#include "Log.h"
#include "../Physics/Collision.h"
#include "../Physics/CollisionManifold.h"
#include "../ECS/ColliderComponent.h"
#include "../ECS/CircleColliderComponent.h"
#include "../ECS/RectangleColliderComponent.h"
#include "../ECS_User/Collider.h"
#include "../Physics/CollisionAlgo.h"


namespace ME
{
	//
	// Initialize Members
	//
	Window Engine::m_Window = Window();
	Renderer Engine::m_Renderer = Renderer();
	ECS Engine::m_ECS = ECS();
	Camera Engine::m_MainCamera = Camera();
	Debug Engine::m_Debug = Debug();
	EngineTime Engine::m_Time = EngineTime();
	Input Engine::m_Input = Input();
	TextureContainer Engine::m_Textures = TextureContainer();
	FontContainer Engine::m_Fonts = FontContainer();
	SDL_Event Engine::m_Event = SDL_Event();
	Engine::State Engine::m_State = Engine::State::Null;


	// 
	// Initialize SDL2
	//
	void Engine::Init(const char* title, const int width, const int height)
	{
		SDLCall(SDL_Init(SDL_INIT_VIDEO));
		SDLCall(TTF_Init());
		SDLCall(IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG));

		m_Window = Window(title, width, height);
		m_Renderer = Renderer(m_Window);
		m_Textures = TextureContainer(100, m_Renderer);
		m_Fonts = FontContainer(10);
		//m_Debug = Debug(&m_Renderer);

		m_State = State::Init;

		m_MainCamera = Camera(AddEntity().AddComponent<Camera>().GetEntityID(), &m_ECS);	
	}

	//
	// Check SDL2 Error
	//
	bool Engine::CheckSDLError()
	{
		std::string error = SDL_GetError();
		SDL_ClearError();
		if (error.size() == 0) return false;
		else if (error == "Not a PNG") return false;
		else
		{
			Log::PrintToLog("[SDL][Error]", error);
			return true;
		}
	}

	void Engine::Start()
	{
		if (m_State != State::Init) return;
		
		Run();
	}

	void Engine::End()
	{
		m_State = State::Init;
	}

	void Engine::ActivateDebug(const char* fontFilePath)
	{

	}

	void Engine::DisableDebug()
	{

	}

	//
	// Returns a new entity that can contain components.
	//
	Entity Engine::AddEntity()
	{
		if (m_State == State::Null) return Entity();
		return Entity(&m_ECS, m_ECS.AddEntity());
	}

	//
	// Destroys the entity and all its components.
	//
	void Engine::DestroyEntity(Entity entity)
	{
		if (m_State != State::Init) return;
		m_ECS.DestroyEntity(entity.GetID());
	}

	//
	// Adds a texture to the engine using a filePath.
	// Supports PNG and JPG/JPEG files.
	//
	Texture Engine::AddTexture(const char* filePath)
	{
		if (m_State != State::Init) return Texture();
		return Texture(m_Textures.Add(filePath, m_Renderer)->GetID());
	}

	//
	// Adds a font to the engine using a filePath.
	// Supports TTF files.
	//
	Font Engine::AddFont(const char* filePath)
	{
		if (m_State != State::Init) return Font();
		return Font(m_Fonts.Add(filePath)->GetID());
	}

	//
	// Prints a log to the console with a timestamp in hh:mm:ss format
	//
	void Engine::DebugLog(const char* log)
	{
		int timeInSeconds = m_Time.GetTimeSinceStart() + 0.5;

		int hours = timeInSeconds / 3600;
		int minutes = timeInSeconds / 60 - hours * 60;
		int seconds = timeInSeconds - minutes * 60;

		std::string hh = std::to_string(hours);
		std::string mm = std::to_string(minutes);
		std::string ss = std::to_string(seconds);

		if (hh.length() == 1) hh = "0" + hh;
		if (mm.length() == 1) mm = "0" + mm;
		if (ss.length() == 1) ss = "0" + ss;

		std::cout << "[ME][Debug][" << hh << ":" << mm << ":" << ss << "][" << log << "]\n";
	}

	Time Engine::GetTime()
	{
		return Time(m_Time.GetDeltaTimeInSeconds());
	}

	Camera Engine::GetMainCamera()
	{
		return m_MainCamera;
	}

	bool Engine::GetKey(const unsigned char code)
	{
		return m_Input.GetKey(code);
	}

	bool Engine::GetKeyUp(const unsigned char code)
	{
		return m_Input.GetKeyUp(code);
	}

	bool Engine::GetKeyDown(const unsigned char code)
	{
		return m_Input.GetKeyDown(code);
	}

	bool Engine::GetMouse(const unsigned char code)
	{
		return m_Input.GetMouse(code);
	}

	bool Engine::GetMouseUp(const unsigned char code)
	{
		return m_Input.GetMouseUp(code);
	}

	bool Engine::GetMouseDown(const unsigned char code)
	{
		return m_Input.GetMouseDown(code);
	}

	Vector2f Engine::GetWorldMousePosition()
	{
		Vector2f pos = m_Input.GetMousePosition();
		
		pos = m_Renderer.GetWindowPointRelativeToCamera(*m_ECS.GetComponent<TransformComponent>(m_MainCamera.GetEntityID()), pos);

		return pos;
	}

	Vector2f Engine::GetScreenMousePosition()
	{
		return m_Input.GetMousePosition();		
	}

	//
	// Call to start the game loop.
	// Updates components and renders textures every frame.
	// 
	void Engine::Run()
	{
		m_State = State::Running;

		while (m_State == State::Running)
		{
			m_Time.Update();
			UpdateEvents();
			UpdateComponents();
			UpdatePhysics();
			UpdateRenderer();
		}

		m_Renderer.SDLCleanUp();
		m_Window.SDLCleanUp();
	}

	//
	// Polls for SDL2 events.
	// Sets running to false if the window has closed.
	// Updates Input.
	//
	void Engine::UpdateEvents()
	{
		m_Input.UpdateMouse();

		while (SDL_PollEvent(&m_Event))
		{
			if (m_Event.type == SDL_QUIT)
			{
				m_State = State::Init;
			}
			else if (m_Event.type == SDL_MOUSEBUTTONDOWN)
			{
				m_Input.MouseDown(m_Event.button.button);
			}
			else if (m_Event.type == SDL_MOUSEBUTTONUP)
			{
				m_Input.MouseUp(m_Event.button.button);
			}
		}

		

		m_Input.Update();

		//m_Debug.Update(m_Time);

		m_Time.UpdateSubFrame(EngineTime::SubFrameType::Misc);
	}

	
	void Engine::UpdateComponents()
	{
		//
		// Scripts
		//
		std::vector<ScriptComponent*>* scripts = m_ECS.GetScripts();

		for (int i = 0; i < scripts->size(); i++)
		{
			scripts->operator[](i)->Update();
		}

		m_Time.UpdateSubFrame(EngineTime::SubFrameType::Script);
	}

	
	void Engine::UpdatePhysics()
	{
		//
		// Update Rigidbodies
		//
		std::vector<RigidbodyComponent>* bodies = m_ECS.GetComponents<RigidbodyComponent>();

		for (int i = 0; i < bodies->size(); i++)
		{
			bodies->operator[](i).Update(
				*m_ECS.GetComponent<TransformComponent>(bodies->operator[](i).GetEntityID()),
				 m_Time.GetDeltaTimeInSeconds()
			);
		}

		//
		// Get Colliders
		//
		std::vector<CircleColliderComponent>* circleColliders = m_ECS.GetComponents<CircleColliderComponent>();
		std::vector<RectangleColliderComponent>* rectangleColliders = m_ECS.GetComponents<RectangleColliderComponent>();
		std::vector<PolygonColliderComponent>* polygonColliders = m_ECS.GetComponents<PolygonColliderComponent>();
		std::vector<ColliderComponent*> colliders;
		colliders.reserve(circleColliders->size() + rectangleColliders->size());

		for (int i = 0; i < circleColliders->size(); i++)
			colliders.emplace_back(&circleColliders->operator[](i));
			
		for (int i = 0; i < rectangleColliders->size(); i++)
			colliders.emplace_back(&rectangleColliders->operator[](i));

		for (int i = 0; i < polygonColliders->size(); i++)
			colliders.emplace_back(&polygonColliders->operator[](i));

		//
		// Check Collisions and Resolve Collisions
		//

		for (ColliderComponent* a : colliders)
		{
			for (ColliderComponent* b : colliders)
			{
				if (a == b) continue;

				TransformComponent& transformA = *m_ECS.GetComponent<TransformComponent>(a->GetEntityID());
				TransformComponent& transformB = *m_ECS.GetComponent<TransformComponent>(b->GetEntityID());

				CollisionManifold manifold = a->CheckCollision(transformA, b, transformB);

				if (!manifold.HasCollision) continue;

				std::vector<ScriptComponent*> scriptsA = m_ECS.GetScriptsOf(a->GetEntityID());		
				for (ScriptComponent* s : scriptsA) s->OnCollision(Collider(b->GetEntityID(), &m_ECS));

				std::vector<ScriptComponent*> scriptsB = m_ECS.GetScriptsOf(b->GetEntityID());
				for (ScriptComponent* s : scriptsB) s->OnCollision(Collider(a->GetEntityID(), &m_ECS));
			
				RigidbodyComponent* bodyA = m_ECS.GetComponent<RigidbodyComponent>(a->GetEntityID());
				RigidbodyComponent* bodyB = m_ECS.GetComponent<RigidbodyComponent>(b->GetEntityID());

				Collision collision = { manifold, transformA, transformB, bodyA, bodyB };

				SolveCollision(collision);
			}
		}

		m_Time.UpdateSubFrame(EngineTime::SubFrameType::Physics);
	}

	//
	// Adds each renderer component to the rendering queue.
	// Clears the renderer and then presents after rendering all objects on the queue.
	//
	void Engine::UpdateRenderer()
	{
		m_Renderer.Clear();

		//
		// Add sprites to the render queue
		//
		std::vector<SpriteRendererComponent>* spriteRenderers =
			m_ECS.GetComponents<SpriteRendererComponent>();

		SpriteRendererComponent spriteRenderer;

		for (int i = 0; i < spriteRenderers->size(); i++)
		{		
			spriteRenderer = spriteRenderers->operator[](i);
			TransformComponent transform = *m_ECS.GetComponent<TransformComponent>(spriteRenderer.GetEntityID());
			ContainedTexture texture = *m_Textures.GetWithID(spriteRenderer.texture.GetTextureID());

			m_Renderer.Enqueue({
				transform,
				Sprite(texture.GetSDLTexture(), spriteRenderer.colour, texture.GetSize()),
				spriteRenderer.layer
			});
		}

		//
		// Add circles to the render queue
		//
		std::vector<CircleRendererComponent>* circleRenderers =
			m_ECS.GetComponents<CircleRendererComponent>();

		CircleRendererComponent circleRenderer;

		for (int i = 0; i < circleRenderers->size(); i++)
		{
			circleRenderers->operator[](i).CreateSDLTexture(m_Renderer);
			circleRenderer = circleRenderers->operator[](i);

			TransformComponent transform = *m_ECS.GetComponent<TransformComponent>(circleRenderer.GetEntityID());
			int radius = circleRenderer.GetRadius();

			m_Renderer.Enqueue({
				transform,
				Sprite(circleRenderer.GetSDLTexture(), circleRenderer.colour, Vector2i(radius * 2, radius * 2)),
				circleRenderer.layer
			});
		}

		//
		// Add polygons to the render queue
		//
		std::vector<PolygonRendererComponent>* polygonRenderers =
			m_ECS.GetComponents<PolygonRendererComponent>();

		PolygonRendererComponent polygonRenderer;
		
		for (int i = 0; i < polygonRenderers->size(); i++)
		{
			polygonRenderers->operator[](i).CreateSDLTexture(m_Renderer);
			polygonRenderer = polygonRenderers->operator[](i);

			TransformComponent transform = *m_ECS.GetComponent<TransformComponent>(polygonRenderer.GetEntityID());
			transform.position += polygonRenderer.GetOffset();
			
			Vector2i size = Vector2i(polygonRenderer.GetPolygon().GetWidth(), polygonRenderer.GetPolygon().GetHeight());
			m_Renderer.Enqueue({
				transform,
				Sprite(polygonRenderer.GetSDLTexture(), polygonRenderer.colour, size),
				polygonRenderer.layer
			});
		}

		//
		// Add text to the render queue
		//
		std::vector<TextRendererComponent>* textRenderers =
			m_ECS.GetComponents<TextRendererComponent>();

		TextRendererComponent textRenderer;

		for (int i = 0; i < textRenderers->size(); i++)
		{
			std::string filePath = m_Fonts.GetWithID(textRenderers->operator[](i).font.GetFontID())->GetFilePath();

			if (filePath.size() != 0)
			{
				textRenderers->operator[](i).CreateSDLTexture(m_Renderer, filePath.c_str());
				textRenderer = textRenderers->operator[](i);

				TransformComponent transform = *m_ECS.GetComponent<TransformComponent>(textRenderer.GetEntityID());

				m_Renderer.Enqueue({
					transform,
					Sprite(textRenderer.GetSDLTexture(), textRenderer.colour, textRenderer.GetTextureSize()),
					textRenderer.layer
				});
			}			
		}

		m_Renderer.RenderQueue(m_Window, *m_ECS.GetComponent<TransformComponent>(m_MainCamera.GetEntityID()));

		//m_Debug.Render();

		m_Renderer.Present(m_Window);

		m_Time.UpdateSubFrame(EngineTime::SubFrameType::Renderer);
	}

}
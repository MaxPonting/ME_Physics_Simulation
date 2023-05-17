#pragma once

//
// C++
//
#include <iostream>
#include <type_traits>
#include <vector>
#include <algorithm>

//
// ME
//
#include "Window.h"
#include "Debug.h"
#include "Input.h"
#include "../Rendering/Renderer.h"
#include "../Rendering/Sprite.h"
#include "../Rendering/TextureContainer.h"
#include "../Rendering/FontContainer.h"
#include "../ECS/ECS.h"
#include "../ECS/ScriptComponent.h"
#include "../ECS_User/Entity.h"
#include "../ECS_User/ComponentRef.h"
#include "../ECS_User/Camera.h"
#include "../User/Time.h"

namespace ME
{
	//
	// Owns window and render.
	// Starts the game loop when 'Start' is called.
	//	
	class Engine final
	{
	public:

		//
		// Initialization
		//
		static void Init(const char* title, const int width, const int height);

		//
		// Error Checking
		//
		static bool CheckSDLError();
		
		//
		// Start Game
		//
		static void Start();

		//
		// End Game
		//
		static void End();

		//
		// Activate Debug
		//
		static void ActivateDebug(const char* fontFilePath);

		//
		// Disable Debug
		//
		static void DisableDebug();

		//
		// Add/Destroy Entities
		//
		static Entity AddEntity();
		static void DestroyEntity(Entity entity);
		
		//
		// Add Textures/Fonts
		//
		static Texture AddTexture(const char* filePath);
		static Font AddFont(const char* filePath);

		//
		// Debug Log
		//
		static void DebugLog(const char* log);
		
		//
		// Getters
		//
		static Time GetTime();
		static Camera GetMainCamera();
		static bool GetKey(const unsigned char code);
		static bool GetKeyUp(const unsigned char code);
		static bool GetKeyDown(const unsigned char code);
		static bool GetMouse(const unsigned char code);
		static bool GetMouseUp(const unsigned char code);		
		static bool GetMouseDown(const unsigned char code);
		static Vector2f GetWorldMousePosition();
		static Vector2f GetScreenMousePosition();
		
				
	private:

		//
		// Game Loop
		//
		static void Run();
		static void UpdateEvents();		
		static void UpdateComponents();					
		static void UpdatePhysics();		
		static void UpdateRenderer();
				
		static Window m_Window;
		static Renderer m_Renderer;
		static ECS m_ECS;
		static Debug m_Debug;
		static EngineTime m_Time;
		static Input m_Input;
		static Camera m_MainCamera;		
		static SDL_Event m_Event;

		//
		// Texture/Font containers
		//
		static TextureContainer m_Textures;
		static FontContainer m_Fonts;
	
		//
		// Engine State
		//
		enum class State { Null, Init, Running };
		static State m_State;
	};

}

/*
Wrapper for every SDL Call
//
	Prints a SDL error to the console
//
	Breaks if an error occurs
*/
#define SDLCall(x) x; if(ME::Engine::CheckSDLError()) __debugbreak();  

/*
	Wrapper for every TTF Call
//
	Prints a TTF error to the console
//
	Breaks if an error occurs
*/
#define TTFCall(x) x; if(ME::Engine::CheckSDLError()) __debugbreak();  

/* Defines prefix for a SDL Error */
#define SDL_Error "[SDL][Error][" + __LINE__ + "]"

/* Defines prefix for a ME Error */
#define ME_Error "[ME][Error][" + __LINE__ + "]"

/* Define prefix for ME Debug */
#define ME_Debug "[ME][Debug][" + __LINE__ + "]"



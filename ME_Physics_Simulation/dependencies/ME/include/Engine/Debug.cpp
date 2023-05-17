#include "Debug.h"
#include "Engine.h"


namespace ME
{
	Debug::Debug() :
		p_Renderer(nullptr),
		p_Font(nullptr),
		m_Timer(0)
	{}

	/* Creates Debug Text */
	Debug::Debug(Renderer* renderer) :
		p_Renderer(renderer),
		m_Timer(0)
	{
		SDLCall(p_Font = TTF_OpenFont("../Assets/Fonts/clear-sans.regular.ttf", FONT_SIZE));

		m_Texts[1] = DebugText("Driver: " + std::string(renderer->GetInfo().name), Vector2i(), p_Font, *renderer);
		m_Texts[0] = DebugText("FPS:", Vector2i(0, FONT_SIZE), p_Font, *renderer);	
		m_Texts[2] = DebugText("Frame:", Vector2i(0, FONT_SIZE * 2), p_Font, *renderer);
		m_Texts[3] = DebugText("Render:", Vector2i(0, FONT_SIZE * 3), p_Font, *renderer);
		m_Texts[4] = DebugText("Physics:", Vector2i(0, FONT_SIZE * 4), p_Font, *renderer);
		m_Texts[5] = DebugText("Scripts:", Vector2i(0, FONT_SIZE * 5), p_Font, *renderer);
		m_Texts[6] = DebugText("Misc:", Vector2i(0, FONT_SIZE * 6), p_Font, *renderer);
	}
	
	void Debug::Update(const EngineTime& time)
	{
		m_Timer += time.GetDeltaTime();

		if (m_Timer >= UPDATE_TIME_MILLISECONDS)
		{
			m_Texts[0].SetText(*p_Renderer, "FPS: " + std::to_string(time.GetFps()));
			m_Texts[2].SetText(*p_Renderer, "Frame: " + std::to_string(time.GetDeltaTime()).substr(0, 5) + "ms");
			m_Texts[3].SetText(*p_Renderer, "Render: " + std::to_string(time.GetRenderTime()).substr(0, 5) + "ms");
			m_Texts[4].SetText(*p_Renderer, "Physics: " + std::to_string(time.GetPhysicsTime()).substr(0, 5) + "ms");
			m_Texts[5].SetText(*p_Renderer, "Scripts: " + std::to_string(time.GetScriptTime()).substr(0, 5) + "ms");
			m_Texts[6].SetText(*p_Renderer, "Misc: " + std::to_string(time.GetMiscTime()).substr(0, 5) + "ms");

			m_Timer -= UPDATE_TIME_MILLISECONDS;
		}
		
	}

	void Debug::Render()
	{
		for (int i = 0; i < NUM_DEBUG_TEXTS; i++)
		{
			m_Texts[i].Render(*p_Renderer);
		}
	}

	Debug::DebugText::DebugText() :
		m_Text(""),
		p_Font(nullptr),
		p_Texture(nullptr)
	{

	}

	Debug::DebugText::DebugText(std::string text, Vector2i position, TTF_Font* font, const Renderer& renderer) :
		m_Text(text),
		m_Position(position),
		p_Font(font),
		p_Texture(nullptr)
	{
		SetText(renderer, m_Text);
	}

	void Debug::DebugText::SetText(const Renderer& renderer, std::string text)
	{
		m_Text = text;

		if (m_Text.size() == 0) { return; }

		if (p_Texture != nullptr)
		{
			SDLCall(SDL_DestroyTexture(p_Texture));
			p_Texture = nullptr;
		}

		const char* outputText = m_Text.c_str();
		SDL_Surface* surface;
		TTFCall(surface = TTF_RenderText_Blended(p_Font, outputText, SDL_Color{ 0, 255, 0, 255 }));
		
		p_Texture = renderer.CreateTextureFromSurface(surface);

		SDLCall(SDL_FreeSurface(surface));
		
		int w, h;
		SDLCall(SDL_QueryTexture(p_Texture, NULL, NULL, &w, &h));

		m_Sprite = Sprite(p_Texture, TEXT_COLOUR, Vector2i(w, h));
	}

	void Debug::DebugText::Render(const Renderer& renderer)
	{
		if (p_Texture == nullptr) return;

		renderer.RenderSprite(m_Sprite, m_Position);
	}

	
}

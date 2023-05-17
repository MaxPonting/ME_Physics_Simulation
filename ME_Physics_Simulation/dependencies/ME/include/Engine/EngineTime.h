#pragma once

/* C++ */
#include <chrono>
#include <string>

namespace ME
{
	class EngineTime final
	{
	public:

		/* CONSTRUCTOR */
		EngineTime();

		/* ENUM CLASS */
		enum class SubFrameType { Misc, Script, Physics, Renderer };

		/* PUBLIC METHODS */
		void Update();
		void UpdateSubFrame(SubFrameType type);

		/* GETTERS */
		int GetFps() const;
		float GetTimeSinceStart() const;
		float GetDeltaTime() const;
		float GetDeltaTimeInSeconds() const;
		float GetMiscTime() const;
		float GetScriptTime() const;
		float GetPhysicsTime() const;
		float GetRenderTime() const;

	private:

		/* PRIVATE METHODS */
		long GetTimeSinceLastFrame();

		/* PRIVATE MEMBERS */
		std::chrono::time_point<std::chrono::high_resolution_clock> m_LastTickTime;	
		int m_Fps;
		float m_TimeSinceStart;
		float m_DeltaTime;
		float m_CurrentDeltaTime;
		float m_MiscTime;
		float m_ScriptTime;
		float m_PhysicsTime;
		float m_RenderTime;
	};
}


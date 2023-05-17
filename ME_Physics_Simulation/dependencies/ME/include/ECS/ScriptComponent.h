#pragma once

#include "Component.h"
#include "../ECS_User/Entity.h"
#include "../ECS/ECS.h"
#include "../Engine/EngineTime.h"
#include "../ECS_User/Collider.h"

namespace ME
{
	class Entity;
	class ScriptComponent : public Component
	{
	public:

		ScriptComponent();
		ScriptComponent(unsigned int entityID, ECS* ecs);

		void virtual Start() {};
		void virtual Update() {};
		void virtual OnCollision(Collider collider) {};

		template<class C>
		C GetComponent()
		{
			return GetEntity().GetComponent<C>();
		}

		template<class C>
		C AddComponent()
		{
			return GetEntity().AddComponent<C>();
		}

		template<class C>
		bool HasComponent()
		{
			return GetEntity().HasComponent<C>();
		}

		template<class C>
		void DestroyComponent()
		{
			return GetEntity().DestroyComponent<C>();
		}

		template<class C>
		C* AddScript()
		{
			return GetEntity().AddScript<C>();
		}

		template <class C>
		C* GetScript()
		{
			return GetEntity().GetScript<C>();
		}

		template <class C>
		bool HasScript()
		{
			return GetEntity().HasScript<C>();
		}

		template <class C>
		void DestroyScript()
		{
			GetEntity().DestroyScript<C>();
		}

		Entity GetEntity();
				
	private:

		ECS* p_ECS;
		
	};
}



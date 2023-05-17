#pragma once

#include "Entity.h"

namespace ME
{
	class ECS;
	class ComponentRef
	{
	public:

		ComponentRef();
		ComponentRef(unsigned int entityID, ECS* ecs);

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
		unsigned int GetEntityID();

	protected:

		unsigned int m_EntityID;
		ECS* p_ECS;
	
	};
}


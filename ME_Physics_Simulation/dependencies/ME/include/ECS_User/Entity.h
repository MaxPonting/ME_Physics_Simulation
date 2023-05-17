#pragma once

#include <type_traits>

#include "../ECS//ECS.h"

namespace ME
{
	class ComponentRef;
	class Transform;
	class SpriteRenderer;
	class CircleRenderer;
	class PolygonRenderer;
	class TextRenderer;
	class Camera;
	class Rigidbody;
	class Collider;
	class CircleCollider;
	class RectangleCollider;
	class PolygonCollider;
	class ScriptComponent;

	//
	// Related to a set of components.
	//
	class Entity final
	{
	public:

		Entity() :
			p_ECS(nullptr),
			m_ID(0)
		{}

		Entity(ECS* ecs, unsigned int id) :
			p_ECS(ecs),
			m_ID(id)
		{}


		//
		// Adds a new component and relates it to this entity's ID.
		//
		template <class C>
		C AddComponent()
		{
			static_assert(std::is_base_of<ComponentRef, C>::value, "C must inherit from ComponentRef!");

			if (std::is_same<Transform, C>::value)
			p_ECS->AddComponent<TransformComponent>(m_ID);
		
			else if (std::is_same<SpriteRenderer, C>::value)
			p_ECS->AddComponent<SpriteRendererComponent>(m_ID);

			else if (std::is_same<CircleRenderer, C>::value)
			p_ECS->AddComponent<CircleRendererComponent>(m_ID);
			
			else if (std::is_same<PolygonRenderer, C>::value)
			p_ECS->AddComponent<PolygonRendererComponent>(m_ID);

			else if (std::is_same<TextRenderer, C>::value)
			p_ECS->AddComponent<TextRendererComponent>(m_ID);

			else if (std::is_same<Rigidbody, C>::value)
			p_ECS->AddComponent<RigidbodyComponent>(m_ID);

			else if (std::is_same<CircleCollider, C>::value)
			p_ECS->AddComponent<CircleColliderComponent>(m_ID);

			else if (std::is_same<RectangleCollider, C>::value)
			p_ECS->AddComponent<RectangleColliderComponent>(m_ID);

			else if (std::is_same<PolygonCollider, C>::value)
			p_ECS->AddComponent<PolygonColliderComponent>(m_ID);

			else if (std::is_same<Camera, C>::value)
			p_ECS->AddComponent<CameraComponent>(m_ID);
			
			return C(m_ID, p_ECS);
		}

		//
		// Returns a given component of the entity.
		//
		template <class C>
		C GetComponent()
		{
			static_assert(std::is_base_of<ComponentRef, C>::value, "C must be a component!");

			bool has;

			if (std::is_same<Transform, C>::value)
			has = p_ECS->HasComponent<TransformComponent>(m_ID);
			
			else if (std::is_same<SpriteRenderer, C>::value)
			has = p_ECS->HasComponent<SpriteRendererComponent>(m_ID);
			
			else if (std::is_same<CircleRenderer, C>::value)
			has = p_ECS->HasComponent<CircleRendererComponent>(m_ID);
			
			else if (std::is_same<PolygonRenderer, C>::value)
			has = p_ECS->HasComponent<PolygonRendererComponent>(m_ID);

			else if (std::is_same<TextRenderer, C>::value)
			has = p_ECS->HasComponent<TextRendererComponent>(m_ID);

			else if (std::is_same<Rigidbody, C>::value)
			has = p_ECS->HasComponent<RigidbodyComponent>(m_ID);

			else if (std::is_same<CircleCollider, C>::value)
			has = p_ECS->HasComponent<CircleColliderComponent>(m_ID);

			else if (std::is_same<RectangleCollider, C>::value)
			has = p_ECS->HasComponent<RectangleColliderComponent>(m_ID);

			else if (std::is_same<PolygonCollider, C>::value)
			has = p_ECS->HasComponent<PolygonColliderComponent>(m_ID);

			else if (std::is_same<Camera, C>::value)
			has = p_ECS->HasComponent<CameraComponent>(m_ID);

			if (has) return C(m_ID, p_ECS);
			else return C();		
		}

		//
		// Returns true the entity has a given component.
		//
		template <class C>
		bool HasComponent()
		{
			static_assert(std::is_base_of<ComponentRef, C>::value, "C must be a component!");

			if (std::is_same<Transform, C>::value)
			return p_ECS->HasComponent<TransformComponent>(m_ID);
			
			else if (std::is_same<SpriteRenderer, C>::value)
			return p_ECS->HasComponent<SpriteRendererComponent>(m_ID);
			
			else if (std::is_same<CircleRenderer, C>::value)
			return p_ECS->HasComponent<CircleRendererComponent>(m_ID);
			
			else if (std::is_same<PolygonRenderer, C>::value)
			return p_ECS->HasComponent<PolygonRendererComponent>(m_ID);

			else if (std::is_same<TextRenderer, C>::value)
			return p_ECS->HasComponent<TextRendererComponent>(m_ID);

			else if (std::is_same<Rigidbody, C>::value)
			return p_ECS->HasComponent<RigidbodyComponent>(m_ID);

			else if (std::is_same<CircleCollider, C>::value)
			return p_ECS->HasComponent<CircleColliderComponent>(m_ID);

			else if (std::is_same<RectangleCollider, C>::value)
			return p_ECS->HasComponent<RectangleColliderComponent>(m_ID);

			else if (std::is_same<PolygonCollider, C>::value)
			return p_ECS->HasComponent<PolygonColliderComponent>(m_ID);

			else if (std::is_same<Camera, C>::value)
			return p_ECS->HasComponent<CameraComponent>(m_ID);

			return false;
		}

		//
		// Destroys a given component of the entity.
		//
		template <class C>
		void DestroyComponent()
		{
			static_assert(std::is_base_of<ComponentRef, C>::value, "C must be a component!");

			if (std::is_same<Transform, C>::value)
			p_ECS->DestroyComponent<TransformComponent>(m_ID);
			
			else if (std::is_same<SpriteRenderer, C>::value)
			p_ECS->DestroyComponent<SpriteRendererComponent>(m_ID);
			
			else if (std::is_same<CircleRenderer, C>::value)
			p_ECS->DestroyComponent<CircleRendererComponent>(m_ID);
			
			else if (std::is_same<PolygonRenderer, C>::value)
			p_ECS->DestroyComponent<PolygonRendererComponent>(m_ID);

			else if (std::is_same<TextRenderer, C>::value)
			p_ECS->DestroyComponent<TextRendererComponent>(m_ID);

			else if (std::is_same<Rigidbody, C>::value)
			p_ECS->DestroyComponent<RigidbodyComponent>(m_ID);

			else if (std::is_same<CircleCollider, C>::value)
			p_ECS->DestroyComponent<CircleColliderComponent>(m_ID);

			else if (std::is_same<RectangleCollider, C>::value)
			p_ECS->DestroyComponent<RectangleColliderComponent>(m_ID);

			else if (std::is_same<PolygonCollider, C>::value)
			p_ECS->DestroyComponent<PolygonColliderComponent>(m_ID);

			else if (std::is_same<Camera, C>::value)
			p_ECS->DestroyComponent<CameraComponent>(m_ID);
		}

		//
		// Adds a given script to the entity
		//
		template <class C>
		C* AddScript()
		{
			static_assert(std::is_base_of<ScriptComponent, C>::value, "C must be a script!");

			return p_ECS->AddScript<C>(m_ID);
		}

		//
		// Returns a given script of the entity
		//
		template <class C>
		C* GetScript()
		{
			static_assert(std::is_base_of<ScriptComponent, C>::value, "C must be a script!");

			return p_ECS->GetScript<C>(m_ID);
		}

		//
		// Returns true if a entity has a given script
		//
		template <class C>
		bool HasScript()
		{
			static_assert(std::is_base_of<ScriptComponent, C>::value, "C must be a script!");

			return p_ECS->HasScript<C>(m_ID);
		}

		//
		// Destroys a given script of the entity.
		//
		template <class C>
		void DestroyScript()
		{
			static_assert(std::is_base_of<ScriptComponent, C>::value, "C must be a script!");

			return p_ECS->DestroyScript<C>(m_ID);
		}

		//
		// Return this entity's unique ID.
		//
		unsigned int GetID()
		{
			return m_ID;
		}


	private:

		ECS* p_ECS;
		unsigned int m_ID;

	};
}



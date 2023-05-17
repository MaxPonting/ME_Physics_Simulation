#include "ScriptComponent.h"
#include "../ECS_User/Entity.h"

namespace ME
{
	ScriptComponent::ScriptComponent() :
		Component(),
		p_ECS(nullptr)
	{}

	ScriptComponent::ScriptComponent(unsigned int entityID, ECS* ecs) :
		Component(entityID),
		p_ECS(ecs)
	{}

	Entity ScriptComponent::GetEntity()
	{
		return Entity(p_ECS, GetEntityID());
	}
	
}

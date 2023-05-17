#include "Component.h"

namespace ME
{
	Component::Component() :
		m_EntityID(0)
	{}

	Component::Component(unsigned int entityID) :
		m_EntityID(entityID)
	{}

	unsigned int Component::GetEntityID() const
	{
		return m_EntityID;
	}

}

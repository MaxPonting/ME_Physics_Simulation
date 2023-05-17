#include "TransformComponent.h"

namespace ME
{
	TransformComponent::TransformComponent() : 
		Component(),
		position(Vector2f()),
		rotation(0),
		scale(Vector2f(1, 1))
	{}

	TransformComponent::TransformComponent(unsigned int entityID) :
		Component(entityID),
		position(Vector2f()),
		rotation(0),
		scale(Vector2f(1, 1))
	{}
}

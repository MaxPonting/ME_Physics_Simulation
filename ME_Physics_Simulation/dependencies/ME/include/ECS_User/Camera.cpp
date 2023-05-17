#include "Camera.h"

namespace ME
{
	Camera::Camera() :
		ComponentRef()
	{}

	Camera::Camera(unsigned int id, ECS* ecs) :
		ComponentRef(id, ecs)
	{}

}

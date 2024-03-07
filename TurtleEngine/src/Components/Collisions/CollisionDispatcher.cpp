// BoxCollisionComponent.h
#ifndef BOXCOLLISIONCOMPONENT_H
#define BOXCOLLISIONCOMPONENT_H
#include "Components/Collisions/ICollisionComponent.h"
#include "Types/Shapes/BoxShape.h"
#include "Types/Vector2.h"

namespace Turtle
{
	class BoxCollisionComponent : public ICollisionComponent
	{
	public:
		BoxCollisionComponent() = delete;
		BoxCollisionComponent(GameObject* parent, const std::string& name, BoxShape& boxCollision);
		BoxCollisionComponent(GameObject* parent, const std::string& name, Vector2f& location, float width, float height);
	};
}
#endif // !BOXCOLLISIONCOMPONENT_H


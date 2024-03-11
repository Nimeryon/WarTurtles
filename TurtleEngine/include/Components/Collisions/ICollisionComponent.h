// ICollisionComponent.h
#ifndef ICOLLISIONCOMPONENT_H
#define ICOLLISIONCOMPONENT_H
#include "Components/Component.h"
#include "Components/Transform.h"
#include "Types/Vector2.h"

namespace Turtle
{
	class ICollisionComponent : public Component
	{
	public:
		ICollisionComponent() = delete;
		ICollisionComponent(GameObject* parent, const std::string& name);

		virtual Vector2f GetCenter() const = 0;
	};
}
#endif // ICOLLISIONCOMPONENT_H


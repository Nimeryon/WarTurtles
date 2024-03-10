// ICollisionComponent.h
#ifndef ICOLLISIONCOMPONENT_H
#define ICOLLISIONCOMPONENT_H
#include "Components/Component.h"
#include "Components/Transform.h"
#include "Types/Shapes/IShape.h"
#include "Types/Vector2.h"

namespace Turtle
{
	class ICollisionComponent : public Component
	{
	public:
		ICollisionComponent() = delete;
		ICollisionComponent(GameObject* parent, const std::string& name);
		virtual ~ICollisionComponent();

		void FixedUpdate(const Time& fixedTime) override;

		virtual void UpdateCollisionTransform(Transform& transform) = 0;

		virtual const IShape& GetShape() const = 0;
	};
}
#endif // !ICOLLISIONCOMPONENT_H


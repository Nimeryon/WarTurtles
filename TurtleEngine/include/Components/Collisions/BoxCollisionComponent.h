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
		BoxCollisionComponent(GameObject* parent, const std::string& name, Vector2f& location, float rotation, float width, float height);

		void UpdateCollisionTransform(Transform& transform) override;
		const BoxShape& GetShape() const override;

	private:
		BoxShape CollisionBox;
	};
}
#endif // !BOXCOLLISIONCOMPONENT_H


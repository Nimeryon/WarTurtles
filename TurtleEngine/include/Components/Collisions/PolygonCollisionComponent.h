// PolygonCollisionComponent.h
#ifndef POLYGONCOLLISIONCOMPONENT_H
#define POLYGONCOLLISIONCOMPONENT_H
#include "Components/Collisions/ICollisionComponent.h"
#include "Types/Shapes/PolygonShape.h"
#include "Types/Vector2.h"

namespace Turtle
{
	class PolygonCollisionComponent : public ICollisionComponent
	{
	public:
		PolygonCollisionComponent() = delete;
		explicit PolygonCollisionComponent(GameObject* parent, const std::string& name = "Collision Component (Polygon)");
		PolygonCollisionComponent(GameObject* parent, const std::string& name, PolygonShape& polygonCollision);
		PolygonCollisionComponent(GameObject* parent, const std::string& name, Vector2f& location, float rotation, float width, float height);

		void UpdateCollisionTransform(Transform& transform) override;
		const PolygonShape& GetShape() const override;

		void InitCollisionParameters(PolygonShape& polygonCollision);
		void InitCollisionParameters(Vector2f& location, float rotation, float width, float height);

	private:
		PolygonShape CollisionPolygon;
	};
}
#endif // !POLYGONCOLLISIONCOMPONENT_H

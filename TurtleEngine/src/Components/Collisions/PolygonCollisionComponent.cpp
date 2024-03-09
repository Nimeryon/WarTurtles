#include "Components/Collisions/PolygonCollisionComponent.h"
#include "Types/Shapes/BoxShape.h"

Turtle::PolygonCollisionComponent::PolygonCollisionComponent(GameObject* parent, const std::string& name, PolygonShape& polygonCollision) : ICollisionComponent(parent,name), CollisionPolygon(polygonCollision)
{
}

Turtle::PolygonCollisionComponent::PolygonCollisionComponent(GameObject* parent, const std::string& name, Vector2f& location, float rotation, float width, float height) : ICollisionComponent(parent, name), CollisionPolygon(BoxShape(location, rotation, width, height))
{
}

void Turtle::PolygonCollisionComponent::UpdateCollisionTransform(Transform& transform)
{
	//TO DO
}

const Turtle::PolygonShape& Turtle::PolygonCollisionComponent::GetShape() const
{
	return CollisionPolygon;
}

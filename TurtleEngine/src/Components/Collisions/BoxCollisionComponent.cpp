#include "Components/Collisions/BoxCollisionComponent.h"

Turtle::BoxCollisionComponent::BoxCollisionComponent(GameObject* parent, const std::string& name, BoxShape& boxCollision) : ICollisionComponent(parent,name), CollisionBox(boxCollision)
{
}

Turtle::BoxCollisionComponent::BoxCollisionComponent(GameObject* parent, const std::string& name, Vector2f& location, float rotation, float width, float height) : ICollisionComponent(parent, name), CollisionBox(BoxShape(location, rotation, width, height))
{
}

void Turtle::BoxCollisionComponent::UpdateCollisionTransform(Transform& transform)
{
	//TO DO
}

const Turtle::BoxShape& Turtle::BoxCollisionComponent::GetShape() const
{
	return CollisionBox;
}

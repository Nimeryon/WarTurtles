#include "Components/Collisions/CircleCollisionComponent.h"

Turtle::CircleCollisionComponent::CircleCollisionComponent(GameObject* parent, const std::string& name) : ICollisionComponent(parent, name)
{
	SetActive(false);
}

Turtle::CircleCollisionComponent::CircleCollisionComponent(GameObject* parent, const std::string& name, CircleShape& circleCollision) : ICollisionComponent(parent,name), CollisionCircle(circleCollision)
{
}

Turtle::CircleCollisionComponent::CircleCollisionComponent(GameObject* parent, const std::string& name, Vector2f& center, float radius) : ICollisionComponent(parent, name), CollisionCircle(CircleShape(center,radius))
{
}

void Turtle::CircleCollisionComponent::UpdateCollisionTransform(Transform& transform)
{
	//TO DO
}


const Turtle::CircleShape& Turtle::CircleCollisionComponent::GetShape() const
{
	return CollisionCircle;
}

void Turtle::CircleCollisionComponent::InitCollisionParameters(CircleShape& circleCollision)
{
	CollisionCircle = circleCollision;
	SetActive(true);
}

void Turtle::CircleCollisionComponent::InitCollisionParameters(Vector2f& center, float radius)
{
	CollisionCircle = CircleShape{ center,radius };
	SetActive(true);
}

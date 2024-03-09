#include "Components/Collisions/ICollisionComponent.h"

Turtle::ICollisionComponent::ICollisionComponent(GameObject* parent, const std::string& name) : Component(parent,name)
{
}

Turtle::ICollisionComponent::~ICollisionComponent()
{
}

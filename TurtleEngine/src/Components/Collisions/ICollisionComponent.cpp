#include "Components/Collisions/ICollisionComponent.h"
#include "GameObjects/GameObject.h"

Turtle::ICollisionComponent::ICollisionComponent(GameObject* parent, const std::string& name) : 
	Component(parent, name)
{
}
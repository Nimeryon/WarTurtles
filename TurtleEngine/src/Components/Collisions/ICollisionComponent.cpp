#include "Components/Collisions/ICollisionComponent.h"
#include "GameObjects/GameObject.h"

Turtle::ICollisionComponent::ICollisionComponent(GameObject* parent, const std::string& name) : Component(parent,name)
{
}

Turtle::ICollisionComponent::~ICollisionComponent()
{
}

void Turtle::ICollisionComponent::FixedUpdate(const Time& fixedTime)
{
	if (m_parent->GetComponent<Physic>()) {// Have physics = can move (change it with a variable "is static" ?
		UpdateCollisionTransform(*m_parent->GetTransform());
	}
}

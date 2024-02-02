#include "Components/Component.h"

Turtle::Component::Component(GameObject* parent, const std::string& name) :
	INamable(name),
	m_parent(parent)
{
}
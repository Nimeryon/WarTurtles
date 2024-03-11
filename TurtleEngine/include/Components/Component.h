// Component.h
#ifndef COMPONENT_H // include guard
#define COMPONENT_H
#include "Interfaces/IActivable.h"
#include "Interfaces/INamable.h"
#include "Interfaces/IObject.h"

namespace Turtle
{
class GameObject;

class Component : public INamable, public IObject, public IActivable
{
public:
	Component() = delete;
	Component(GameObject* parent, const std::string& name);

	virtual ~Component() = default;

protected:
	GameObject* m_parent;
};
}

#endif /* COMPONENT_H */
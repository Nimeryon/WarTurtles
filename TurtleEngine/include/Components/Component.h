// Component.h
#ifndef COMPONENT_H // include guard
#define COMPONENT_H
#include "Interfaces/IActivable.h"
#include "Interfaces/INamable.h"
#include "Interfaces/IObject.h"

namespace Turtle
{
class Component : public INamable, public IObject, public IActivable
{
public:
	Component(const std::string& name);
};
}

#endif /* COMPONENT_H */
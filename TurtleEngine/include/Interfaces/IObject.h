// IObject.h
#ifndef IOBJECT_H // include guard
#define IOBJECT_H
#include "Utils/Window.h"
#include "Utils/Time.h"
#include "Managers/InputManager.h"

namespace Turtle
{
struct IObject
{
	virtual ~IObject() = default;

	// Called once when object created
	virtual void OnCreate() {}
	// Called once when object destroyed
	virtual void OnDestroyed() {}

	// Called every frame in first
	virtual void ProcessInputs(const InputManager& inputManager) {}
	// Called every frame
	virtual void Update(const Time& deltaTime) {}
	// Called logic time frame
	virtual void FixedUpdate(const Time& fixedTime) {}
	// Called every frame before GUI
	virtual void Draw(Window& window) {}
	// Called every frame after draw before GUI if debug true
	virtual void DebugDraw(Window& window) {}
	// Called every frame in last
	virtual void Gui(Window& window, const Time& deltaTime) {}
};
}

#endif /* IOBJECT_H */
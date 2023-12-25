// Scene.h
#ifndef SCENE_H // include guard
#define SCENE_H

namespace Turtle
{
class Time;

class Scene
{
public:
	virtual ~Scene() = default;

	// Called once when scene created
	virtual void OnCreate() {}
	// Called once when scene destroyed
	virtual void OnDestroyed() {}

	// Called every time scene is enabled
	virtual void OnEnabled() {}
	// Called every time scene is disabled
	virtual void OnDisabled() {}

	// Called every frame in first
	virtual void ProcessInputs() {}
	// Called every frame
	virtual void Update(const Time& deltaTime) {}
	// Called logic time frame
	virtual void FixedUpdate(const Time& fixedTime) {}
	// Called every frame before GUI
	virtual void Draw(sf::RenderWindow& window) {}
	// Called every frame in last
	virtual void Gui(const Time& deltaTime) {}
};
}

#endif /* SCENE_H */
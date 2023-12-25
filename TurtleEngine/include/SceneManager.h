// SceneManager.h
#ifndef SCENE_MANAGER_H // include guard
#define SCENE_MANAGER_H
#include <memory>
#include <unordered_map>

#include "Utils/Singleton.h"
#include "Scene.h"

namespace sf
{
	class RenderWindow;
}

namespace Turtle
{
class Time;
class Scene;
	
using ScenePtr = std::unique_ptr<Scene>;
	
class SceneManager : public Singleton<SceneManager>
{
public:
	unsigned int AddScene(ScenePtr scene);
	void RemoveScene(unsigned int sceneID);
	void SetScene(unsigned int sceneID);

	// Pass through methods that will call current scene methods

	void ProcessInputs() const;
	void Update(const Time& deltaTime) const;
	void FixedUpdate(const Time& fixedTime) const;
	void Draw(sf::RenderWindow& window) const;
	void Gui(const Time& deltaTime) const;

	friend class Singleton;

protected:
	SceneManager();

private:
    std::unordered_map<unsigned int, ScenePtr> m_scenes;

    Scene* m_currentScene;
    unsigned int m_insertedSceneID;
};
}

#endif /* SCENE_MANAGER_H */
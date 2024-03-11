// SceneManager.h
#ifndef SCENE_MANAGER_H // include guard
#define SCENE_MANAGER_H
#include <memory>
#include <unordered_map>

#include "Utils/Singleton.h"
#include "Utils/Window.h"
#include "Utils/Time.h"
#include "Scene.h"

namespace Turtle
{
class Scene;
	
using ScenePtr = std::unique_ptr<Scene>;
	
class SceneManager : public Singleton<SceneManager>
{
public:
	Scene* GetCurrentScene() const;

	unsigned int AddScene(ScenePtr scene, bool setScene = false);
	void RemoveScene(unsigned int sceneID);
	void SetScene(unsigned int sceneID);
	// Set scene with current scene id plus one
	void NextScene();
	// Set scene with current scene id minus one
	void PreviousScene();

	// Pass through methods that will call current scene methods

	void ProcessInputs() const;
	void Update(const Time& deltaTime) const;
	void FixedUpdate(const Time& fixedTime) const;
	void Draw(Window& window) const;
	void DebugDraw(Window& window) const;
	void Gui(const Time& deltaTime) const;

	friend class Singleton;

protected:
	SceneManager();

private:
    std::unordered_map<unsigned int, ScenePtr> m_scenes;

    Scene* m_currentScene;
	unsigned int m_currentSceneID;
    unsigned int m_insertedSceneID;
};
}

#endif /* SCENE_MANAGER_H */
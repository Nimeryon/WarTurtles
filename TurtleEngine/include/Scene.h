// Scene.h
#ifndef SCENE_H // include guard
#define SCENE_H
#include "GameObjects/GameObject.h"
#include "Managers/AudioManager.h"
#include "Managers/TextureManager.h"
#include "Managers/FontManager.h"
#include "Managers/PhysicManager.h"
#include "Interfaces/IObject.h"

namespace Turtle
{
class SceneManager;

class Scene : public IObject
{
public:
	Scene();

	static const Scene* Current();

	const AudioManager& GetAudioManager() const;
	const TextureManager& GetTextureManager() const;
	const FontManager& GetFontManager() const;
	const PhysicManager& GetPhysicManager() const;

	// =====================
	// Object Properties
	// =====================

	void OnCreate() override;
	void OnDestroyed() override;

	void ProcessInputs() override;
	void Update(const Time& deltaTime) override;
	void FixedUpdate(const Time& fixedTime) override;
	void Draw(Window& window) override;
	void DebugDraw(Window& window) override;
	void Gui(Window& window, const Time& deltaTime) override;

	// =====================
	// Game Objects
	// =====================

	GameObject* Create(const std::string& name = "Empty Object");
	GameObject* Create(GameObject* parent, const std::string& name = "Empty Object");
	GameObject* Create(const Vector2f& position, float rotation, const std::string& name = "Empty Object");
	GameObject* Create(GameObject* parent, const Vector2f& position, float rotation, const std::string& name = "Empty Object");

	template<typename Type>
	Type* Create(const std::string& name = "Empty Object");
	template<typename Type>
	Type* Create(GameObject* parent, const std::string& name = "Empty Object");
	template<typename Type>
	Type* Create(const Vector2f& position, float rotation, const std::string& name = "Empty Object");
	template<typename Type>
	Type* Create(GameObject* parent, const Vector2f& position, float rotation, const std::string& name = "Empty Object");

	void Destroy(GameObject* object);

	// Returns first Object with name
	GameObject* Find(const std::string& name);
	// Returns all Object with name
	std::vector<GameObject*> Finds(const std::string& name);

	void NeedObjectsSorting();

protected:
	AudioManager m_audioManager; 
	TextureManager m_textureManager;
	FontManager m_fontManager;
	PhysicManager m_physicManager;

private:
	std::vector<std::unique_ptr<GameObject>> m_objects;
	std::vector<std::unique_ptr<GameObject>> m_objectsToCreate;
	std::vector<GameObject*> m_objectsToDestroy;
	bool m_needObjectCreate;
	bool m_needObjectDestroy;
	bool m_needObjectsSorting;

	GameObject* m_findCacheObject;

	void _HandleObjectCreation();
	void _HandleObjectDestroy();

	friend SceneManager;
};
}

#include "Scene.hxx"

#endif /* SCENE_H */
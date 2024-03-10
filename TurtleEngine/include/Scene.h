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
class Scene : public IObject
{
public:
	Scene();

	static const Scene* Current();

	const AudioManager& GetAudioManager() const;
	const TextureManager& GetTextureManager() const;
	const FontManager& GetFontManager() const;
	const PhysicManager& GetPhysicManager() const;
	void test();

	// =====================
	// Object Properties
	// =====================

	void OnCreate() override;
	void OnDestroyed() override;

	void ProcessInputs() override;
	void Update(const Time& deltaTime) override;
	void FixedUpdate(const Time& fixedTime) override;
	void Draw(Window& window) override;
	void Gui(const Time& deltaTime) override;

	// =====================
	// Game Objects
	// =====================

	GameObject* Create(const std::string& name = "Empty Object");
	GameObject* Create(GameObject* parent, const std::string& name = "Empty Object");
	GameObject* Create(const Vector2f& position, float rotation, const std::string& name = "Empty Object");
	GameObject* Create(GameObject* parent, const Vector2f& position, float rotation, const std::string& name = "Empty Object");

	void Destroy(GameObject* object);

	// Returns first Object with name
	GameObject* Find(const std::string& name);
	// Returns all Object with name
	std::vector<GameObject*> Finds(const std::string& name);

protected:
	AudioManager m_audioManager;
	TextureManager m_textureManager;
	FontManager m_fontManager;
	PhysicManager m_physicManager;

private:
	std::vector<std::unique_ptr<GameObject>> m_objects;
	GameObject* m_findCacheObject;
};
}

#endif /* SCENE_H */
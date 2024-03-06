#include "Scene.h"

#include "Managers/SceneManager.h"

Turtle::Scene::Scene() :
	m_findCacheObject(nullptr)
{}

const Turtle::Scene* Turtle::Scene::Current()
{
    return SceneManager::Instance().GetCurrentScene();
}

const Turtle::AudioManager& Turtle::Scene::GetAudioManager() const { return m_audioManager; }
const Turtle::TextureManager& Turtle::Scene::GetTextureManager() const { return m_textureManager; }
const Turtle::FontManager& Turtle::Scene::GetFontManager() const { return m_fontManager; }
const Turtle::PhysicManager& Turtle::Scene::GetPhysicManager() const { return m_physicManager; }

// =====================
// Object Properties
// =====================

void Turtle::Scene::OnCreate()
{
	for (auto& object : m_objects)
	{
		if (object->IsActive())
			object->OnCreate();
	}
}
void Turtle::Scene::OnDestroyed()
{
	for (auto& object : m_objects)
	{
		if (object->IsActive())
			object->OnDestroyed();
	}
}

void Turtle::Scene::ProcessInputs()
{
	for (auto& object : m_objects)
	{
		if (object->IsActive())
			object->ProcessInputs();
	}
}
void Turtle::Scene::Update(const Time& deltaTime)
{
	for (auto& object : m_objects)
	{
		if (object->IsActive())
			object->Update(deltaTime);
	}
}
void Turtle::Scene::FixedUpdate(const Time& fixedTime)
{
	for (auto& object : m_objects)
	{
		if (object->IsActive())
			object->FixedUpdate(fixedTime);
	}
}
void Turtle::Scene::Draw(Window& window)
{
	for (auto& object : m_objects)
	{
		if (object->IsActive())
			object->Draw(window);
	}
}
void Turtle::Scene::Gui(const Time& deltaTime)
{
	for (auto& object : m_objects)
	{
		if (object->IsActive())
			object->Gui(deltaTime);
	}
}

// =====================
// Game Objects
// =====================

Turtle::GameObject* Turtle::Scene::Find(const std::string& name)
{
	if (m_findCacheObject && m_findCacheObject->GetName() == name)
	{
		return m_findCacheObject;
	}

	for (auto& object : m_objects)
	{
		if (object->GetName() == name)
		{
			m_findCacheObject = object.get();
			return object.get();
		}
	}

	return nullptr;
}
std::vector<Turtle::GameObject*> Turtle::Scene::Finds(const std::string& name)
{
	std::vector<GameObject*> objects;

	if (m_findCacheObject && m_findCacheObject->GetName() == name)
	{
		objects.emplace_back(m_findCacheObject);
	}

	for (auto& object : m_objects)
	{
		if (object->GetName() == name)
		{
			m_findCacheObject = object.get();
			objects.emplace_back(object.get());
		}
	}

	return objects;
}
#include "Scene.h"

#include "Managers/SceneManager.h"

Turtle::Scene::Scene() :
	m_findCacheObject(nullptr)
{
}

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

Turtle::GameObject* Turtle::Scene::Create(const std::string& name)
{
	std::unique_ptr<GameObject> object = std::make_unique<GameObject>(name);
	GameObject* objectPtr = object.get();
	m_objects.emplace_back(std::move(object));

	objectPtr->OnCreate();
	return objectPtr;
}
Turtle::GameObject* Turtle::Scene::Create(GameObject* parent, const std::string& name)
{
	std::unique_ptr<GameObject> object = std::make_unique<GameObject>(name, parent);
	GameObject* objectPtr = object.get();
	m_objects.emplace_back(std::move(object));

	objectPtr->OnCreate();
	return objectPtr;
}
Turtle::GameObject* Turtle::Scene::Create(const Vector2f& position, float rotation, const std::string& name)
{
	GameObject* object = Create(name);
	object->GetTransform()->SetPosition(position);
	object->GetTransform()->SetRotation(rotation);

	return object;
}

Turtle::GameObject* Turtle::Scene::Create(GameObject* parent, const Vector2f& position, float rotation, const std::string& name)
{
	GameObject* object = Create(parent, name);
	object->GetTransform()->SetPosition(position);
	object->GetTransform()->SetRotation(rotation);

	return object;
}

void Turtle::Scene::Destroy(GameObject* object)
{
	if (object == nullptr)
		return;

	const auto& it = std::find_if(
		m_objects.begin(),
		m_objects.end(),
		[object](const std::unique_ptr<GameObject>& _object) { return object == _object.get(); }
	);
	if (it != m_objects.end())
	{
		object->OnDestroyed();
		m_objects.erase(it);
	}
}

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
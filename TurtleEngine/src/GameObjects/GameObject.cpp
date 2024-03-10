#include "GameObjects/GameObject.h"

#include "Managers/SceneManager.h"
#include "Utils/String.h"

Turtle::GameObject::GameObject(const std::string& name, GameObject* parent) :
	INamable(name),
	m_transform(nullptr),
	m_parent(nullptr)
{
	m_transform = AddComponent<Transform>();
	SetParent(parent);
}

Turtle::GameObject* Turtle::GameObject::Create(const std::string& name)
{
	return SceneManager::Instance().GetCurrentScene()->Create(name);
}
Turtle::GameObject* Turtle::GameObject::Create(GameObject* parent, const std::string& name)
{
	return SceneManager::Instance().GetCurrentScene()->Create(parent, name);
}
Turtle::GameObject* Turtle::GameObject::Create(const Vector2f& position, float rotation, const std::string& name)
{
	return SceneManager::Instance().GetCurrentScene()->Create(position, rotation, name);
}
Turtle::GameObject* Turtle::GameObject::Create(GameObject* parent, const Vector2f& position, float rotation, const std::string& name)
{
	return SceneManager::Instance().GetCurrentScene()->Create(parent, position, rotation, name);
}

void Turtle::GameObject::Destroy(GameObject* object)
{
	SceneManager::Instance().GetCurrentScene()->Destroy(object);
}

Turtle::GameObject* Turtle::GameObject::Find(const std::string& name)
{
	return SceneManager::Instance().GetCurrentScene()->Find(name);
}

std::vector<Turtle::GameObject*> Turtle::GameObject::Finds(const std::string& name)
{
	return SceneManager::Instance().GetCurrentScene()->Finds(name);
}

// =====================
// Object Properties
// =====================

void Turtle::GameObject::Destroy()
{
	Destroy(this);
}

void Turtle::GameObject::OnCreate()
{
	for (auto& component : m_components)
	{
		if (component->IsActive())
			component->OnCreate();
	}
}
void Turtle::GameObject::OnDestroyed()
{
	for (auto& component : m_components)
	{
		if (component->IsActive())
			component->OnDestroyed();
	}
}

void Turtle::GameObject::ProcessInputs()
{
	for (auto& component : m_components)
	{
		if (component->IsActive())
			component->ProcessInputs();
	}
}
void Turtle::GameObject::Update(const Time& deltaTime)
{
	for (auto& component : m_components)
	{
		if (component->IsActive())
			component->Update(deltaTime);
	}
}
void Turtle::GameObject::FixedUpdate(const Time& fixedTime)
{
	for (auto& component : m_components)
	{
		if (component->IsActive())
			component->FixedUpdate(fixedTime);
	}
}
void Turtle::GameObject::Draw(Window& window)
{
	for (auto& component : m_components)
	{
		if (component->IsActive())
			component->Draw(window);
	}
}
void Turtle::GameObject::Gui(const Time& deltaTime)
{
	for (auto& component : m_components)
	{
		if (component->IsActive())
			component->Gui(deltaTime);
	}
}

// =====================
// Tags
// =====================

std::vector<std::string> Turtle::GameObject::GetTags() const
{
	return String::Split(m_tags, ',');
}
const std::string& Turtle::GameObject::GetTagsString() const { return m_tags; }
bool Turtle::GameObject::CompareTags(const std::string& tags) const
{
	return m_tags == tags;
}
bool Turtle::GameObject::CompareTags(const std::vector<std::string>& tags) const
{
	return m_tags == String::Concat(tags, ",");
}

void Turtle::GameObject::AddTags(const std::string& tagsToAdd)
{
	auto newTags = String::Split(tagsToAdd, ',');
	auto tags = GetTags();
	tags.insert(tags.begin(), newTags.begin(), newTags.end());

	m_tags = String::Concat(tags, ",");
}
void Turtle::GameObject::RemoveTags(const std::string& tagsToRemove)
{
	const auto tagsToRemoveList = String::Split(tagsToRemove, ',');
	const auto tags = GetTags();

	std::vector<std::string> newTags;
	for (const std::string& tag : tags)
	{
		bool needRemove = false;
		for (const std::string& tagToRemove : tagsToRemoveList)
		{
			if (tag == tagToRemove)
			{
				needRemove = true;
				break;
			}
		}

		if (!needRemove)
		{
			newTags.emplace_back(tag);
		}

		m_tags = String::Concat(newTags, ",");
	}
}

// =====================
// Children
// =====================

Turtle::GameObject* Turtle::GameObject::GetChild(const int& index) const
{
	return m_children[index];
}
Turtle::GameObject* Turtle::GameObject::GetChildWidthName(const std::string& name) const
{
	for (GameObject* child : m_children)
	{
		if (child->GetName() == name)
		{
			return child;
		}
	}

	return nullptr;
}
Turtle::GameObject* Turtle::GameObject::GetChildWithTags(const std::string& tags) const
{
	for (GameObject* child : m_children)
	{
		if (child->CompareTags(tags))
		{
			return child;
		}
	}

	return nullptr;
}
std::vector<Turtle::GameObject*> Turtle::GameObject::GetChildrenWithName(const std::string& name) const
{
	std::vector<GameObject*> gameObjects;
	for (GameObject* child : m_children)
	{
		if (child->GetName() == name)
		{
			gameObjects.emplace_back(child);
		}
	}

	return gameObjects;
}
std::vector<Turtle::GameObject*> Turtle::GameObject::GetChildrenWithTags(const std::string& tags) const
{
	std::vector<GameObject*> gameObjects;
	for (GameObject* child : m_children)
	{
		if (child->CompareTags(tags))
		{
			gameObjects.emplace_back(child);
		}
	}

	return gameObjects;
}
const std::vector<Turtle::GameObject*>& Turtle::GameObject::GetChildren() const { return m_children; }

void Turtle::GameObject::SetParent(GameObject* object)
{
	if (object == m_parent)
	{
		return;
	}

	if (m_parent != nullptr)
	{
		m_parent->RemoveChild(this);
	}

	m_parent = object;
	if (m_parent != nullptr)
	{
		m_parent->AddChild(this);
	}
}
void Turtle::GameObject::AddChild(GameObject* object)
{
	if (object == nullptr)
	{
		return;
	}

	const auto it = std::find(m_children.begin(), m_children.end(), object);
	if (it == m_children.end())
	{
		m_children.emplace_back(object);
		object->SetParent(this);
	}
}
void Turtle::GameObject::RemoveChild(GameObject* object)
{
	if (object == nullptr)
	{
		return;
	}

	const auto it = std::find(m_children.begin(), m_children.end(), object);
	if (it != m_children.end())
	{
		m_children.erase(it);
		object->RemoveFromParent();
	}

}
void Turtle::GameObject::RemoveFromParent()
{
	SetParent(nullptr);
}

// =====================
// Components
// =====================

Turtle::Transform* Turtle::GameObject::GetTransform() const { return m_transform; }

const std::vector<std::unique_ptr<Turtle::Component>>& Turtle::GameObject::GetComponents() const { return m_components; }
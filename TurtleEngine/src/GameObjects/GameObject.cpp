#include "GameObjects/GameObject.h"
#include "Utils/String.h"

Turtle::GameObject::GameObject(const std::string& name, GameObject* parent, const std::string& tags) :
	INamable(name),
	m_tags(tags),
	m_needTransformUpdate(true)
{
	SetParent(parent);
}

// =====================
// Tags
// =====================

const std::vector<std::string> Turtle::GameObject::GetTags() const
{
	return String::Split(m_tags, ',');
}
const std::string& Turtle::GameObject::GetTagsString() const { return m_tags; }
bool Turtle::GameObject::CompareTags(const std::string& tags) const
{
	return m_tags == tags;
}

void Turtle::GameObject::AddTags(const std::string& tags)
{
	auto newTags = String::Split(tags, ',');
	auto tags = GetTags();
	tags.insert(tags.begin(), newTags.begin(), newTags.end());

	m_tags = String::Concat(tags, ",");
}
void Turtle::GameObject::RemoveTags(const std::string& tags)
{
	
}

// =====================
// Children
// =====================

Turtle::GameObject* Turtle::GameObject::GetChild(const int& index) const
{
	
}
Turtle::GameObject* Turtle::GameObject::GetChildWidthName(const std::string& name) const
{
	
}
Turtle::GameObject* Turtle::GameObject::GetChildWithTags(const std::string& tags) const
{
	
}
const std::vector<Turtle::GameObject*> Turtle::GameObject::GetChildrenWithName(const std::string& name) const
{
	
}
const std::vector<Turtle::GameObject*> Turtle::GameObject::GetChildrenWithTags(const std::string& tags) const
{
	
}
const std::vector<Turtle::GameObject*> Turtle::GameObject::GetChildren() const
{
	
}

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


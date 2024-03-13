// GameObject.hxx
#ifndef GAME_OBJECT_HXX // include guard
#define GAME_OBJECT_HXX
#include <stdexcept>

#include "GameObject.h"
#include "Components/Transform.h"

template<typename Type>
Type* Turtle::GameObject::Create(const std::string& name)
{
	return SceneManager::Instance().GetCurrentScene()->Create<Type>(name);
}
template<typename Type>
Type* Turtle::GameObject::Create(GameObject* parent, const std::string& name)
{
	return SceneManager::Instance().GetCurrentScene()->Create<Type>(parent, name);
}
template<typename Type>
Type* Turtle::GameObject::Create(const Vector2f& position, float rotation, const std::string& name)
{
	return SceneManager::Instance().GetCurrentScene()->Create<Type>(position, rotation, name);
}
template<typename Type>
Type* Turtle::GameObject::Create(GameObject* parent, const Vector2f& position, float rotation, const std::string& name)
{
	return SceneManager::Instance().GetCurrentScene()->Create<Type>(parent, position, rotation, name);
}

template <typename Type>
Type* Turtle::GameObject::GetComponent() const
{
	static_assert(std::is_base_of_v<Component, Type>);

	for (auto& component : m_components)
	{
		if (Type* castComponent = dynamic_cast<Type*>(component.get()))
		{ 
			if (castComponent->IsActive())
				return castComponent;
		}
	}

	return nullptr;
}
template <typename Type>
Type* Turtle::GameObject::GetOrAddComponent()
{
	Type* component = GetComponent<Type>();
	if (!component)
	{
		return AddComponent<Type>();
	}

	return component;
}

template <typename Type>
Type* Turtle::GameObject::AddComponent()
{
	static_assert(std::is_base_of_v<Component, Type>);

	Type* component = GetComponent<Type>();
	if (component)
	{
		return component;
	}

	std::unique_ptr<Type> newComponent = std::make_unique<Type>(this);
	Type* newComponentPtr = newComponent.get();
	m_components.emplace_back(std::move(newComponent));

	return newComponentPtr;
}
template <typename Type>
void Turtle::GameObject::RemoveComponent()
{
	static_assert(std::is_base_of_v<Component, Type>);
	if (std::is_same_v<Transform, Type>)
	{
		throw std::runtime_error("Can't delete Transform component");
	}

	for (auto it = m_components.begin(); it != m_components.end(); ++it)
	{
		if (dynamic_cast<Type*>(it->get()))
		{
			m_components.erase(it);
			break;
		}
	}
}

#endif /* GAME_OBJECT_HXX */
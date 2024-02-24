// GameObject.hxx
#ifndef GAME_OBJECT_HXX // include guard
#define GAME_OBJECT_HXX
#include "GameObject.h"

template <typename Type>
Type* Turtle::GameObject::GetComponent() const
{
	static_assert(std::is_base_of_v<Component, Type>);

	for (Component* component : m_components)
	{
		if (Type* castComponent = dynamic_cast<Type>(component))
		{
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

	component = std::make_unique<Type>(this);
	m_components.emplace_back(component);
	return component;
}
template <typename Type>
void Turtle::GameObject::RemoveComponent()
{
	static_assert(std::is_base_of_v<Component, Type>);
	if (std::is_base_of_v<Transform, Type>)
	{
		throw "Can't delete Transform component";
	}

	Type* component = GetComponent<Type>();
	auto& it = std::find(m_components.begin(), m_components.end(), component);
	if (it != m_components.end())
	{
		delete component;
		m_components.erase(it);
	}
}

#endif /* GAME_OBJECT_HXX */
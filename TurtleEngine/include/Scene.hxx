// Scene.hxx
#ifndef SCENE_HXX // include guard
#define SCENE_HXX
#include "Scene.h"

template<typename Type>
Type* Turtle::Scene::Create(const std::string& name)
{
	static_assert(std::is_base_of_v<GameObject, Type>);

	m_needObjectCreate = true;

	std::unique_ptr<Type> object = std::make_unique<Type>(name);
	Type* objectPtr = object.get();
	m_objectsToCreate.emplace_back(std::move(object));

	objectPtr->OnCreate();
	return objectPtr;
}
template<typename Type>
Type* Turtle::Scene::Create(GameObject* parent, const std::string& name)
{
	static_assert(std::is_base_of_v<GameObject, Type>);

	m_needObjectCreate = true;

	std::unique_ptr<Type> object = std::make_unique<Type>(name, parent);
	Type* objectPtr = object.get();
	m_objectsToCreate.emplace_back(std::move(object));

	objectPtr->OnCreate();
	return objectPtr;
}
template<typename Type>
Type* Turtle::Scene::Create(const Vector2f& position, float rotation, const std::string& name)
{
	Type* object = Create<Type>(name);
	object->GetTransform()->SetPosition(position);
	object->GetTransform()->SetRotation(rotation);

	return object;
}
template<typename Type>
Type* Turtle::Scene::Create(GameObject* parent, const Vector2f& position, float rotation, const std::string& name)
{
	Type* object = Create<Type>(parent, name);
	object->GetTransform()->SetPosition(position);
	object->GetTransform()->SetRotation(rotation);

	return object;
}

#endif /* SCENE_HXX */
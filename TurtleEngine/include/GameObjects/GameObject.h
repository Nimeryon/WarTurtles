// GameObject.h
#ifndef GAME_OBJECT_H // include guard
#define GAME_OBJECT_H
#include "Interfaces/IActivable.h"
#include "Interfaces/INamable.h"
#include "Interfaces/IObject.h"
#include "Components/Component.h"
#include "Types/Vector2.h"

namespace Turtle
{
class Transform;
class SceneManager;

class GameObject : public INamable, public IObject, public IActivable
{
public:
	explicit GameObject(const std::string& name = "Empty Object", GameObject* parent = nullptr);

	static GameObject* Create(const std::string& name = "Empty Object");
	static GameObject* Create(GameObject* parent, const std::string& name = "Empty Object");
	static GameObject* Create(const Vector2f& position, float rotation, const std::string& name = "Empty Object");
	static GameObject* Create(GameObject* parent, const Vector2f& position, float rotation, const std::string& name = "Empty Object");

	template<typename Type>
	static Type* Create(const std::string& name = "Empty Object");
	template<typename Type>
	static Type* Create(GameObject* parent, const std::string& name = "Empty Object");
	template<typename Type>
	static Type* Create(const Vector2f& position, float rotation, const std::string& name = "Empty Object");
	template<typename Type>
	static Type* Create(GameObject* parent, const Vector2f& position, float rotation, const std::string& name = "Empty Object");

	static void Destroy(GameObject* object);

	// Returns first Object with name
	static GameObject* Find(const std::string& name);
	// Returns all Object with name
	static std::vector<GameObject*> Finds(const std::string& name);

	// =====================
	// Object Properties
	// =====================

	void Destroy();

	void OnCreate() override;
	void OnDestroyed() override;

	virtual void OnCollide(const GameObject& collidingObject);

	void ProcessInputs(const InputManager& inputManager) override;
	void Update(const Time& deltaTime) override;
	void FixedUpdate(const Time& fixedTime) override;
	void Draw(Window& window) override;
	void DebugDraw(Window& window) override;
	void Gui(Window& window, const Time& deltaTime) override;

	// =====================
	// Tags
	// =====================

	std::vector<std::string> GetTags() const;
	const std::string& GetTagsString() const;

	// Tags separated by ',': Player,Object
	bool CompareTags(const std::string& tags) const;
	// Tags separated by ',': Player,Object
	bool CompareTags(const std::vector<std::string>& tags) const;

	// Tags separated by ',': Player,Object
	void AddTags(const std::string& tagsToAdd);
	// Tags separated by ',': Player,Object
	void RemoveTags(const std::string& tagsToRemove);

	// =====================
	// Children
	// =====================

	GameObject* GetParent() const;

	GameObject* GetChild(const int& index) const;
	// Return first child with name
	GameObject* GetChildWidthName(const std::string& name) const;
	// Return first child with tags
	GameObject* GetChildWithTags(const std::string& tags) const;
	// Return all children with name
	std::vector<GameObject*> GetChildrenWithName(const std::string& name) const;
	// Return all children with tags
	std::vector<GameObject*> GetChildrenWithTags(const std::string& tags) const;
	// return all children
	const std::vector<GameObject*>& GetChildren() const;

	void SetParent(GameObject* object);
	void AddChild(GameObject* object);
	void RemoveChild(GameObject* object);
	void RemoveFromParent();

	// =====================
	// Components
	// =====================
	
	Transform* GetTransform() const;

	const std::vector<std::unique_ptr<Component>>& GetComponents() const;

	template<typename Type>
	Type* GetComponent() const;
	template<typename Type>
	Type* GetOrAddComponent();

	template<typename Type>
	Type* AddComponent();
	template<typename Type>
	void RemoveComponent();

	// Transform update

	void NeedTransformUpdate();
	void TransformUpdate();

	// Z Index

	int GetZIndex() const;
	void SetZIndex(int zIndex);

protected:
	// tags separated by ','
	std::string m_tags;

	// Components
	std::vector<std::unique_ptr<Component>> m_components;
	Transform* m_transform;

	int m_zIndex;
	bool m_needTransformUpdate;

	// Objects
	std::vector<GameObject*> m_children;
	GameObject* m_parent;
};
}

#include "GameObject.hxx"

#endif /* GAME_OBJECT_H */
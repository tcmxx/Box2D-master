#pragma once

#include "Box2D\Box2D.h"
#include "Transform.h"
#include <vector>
#include "Component.h"
#include "Physics2D.h"

using namespace std;
class Scene;

class GameObject
{
public:
	~GameObject();

	/// Get the Transform of this game object.
	Transform* GetTransform();
	const Transform* GetTransform() const;


	template <typename T>
	T* GetComponent() const {
		static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");
		for (std::vector<Component*>::size_type i = 0; i != componentVector.size(); i++) {
			T* comp = dynamic_cast<T *>(componentVector[i]);
			if (comp) {
				return comp;
			}
		}
		return nullptr;
	};

	template <typename T>
	inline vector<T*> GetComponents() const {
		static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");
		vector<T*> result;
		for (std::vector<Component*>::size_type i = 0; i != componentVector.size(); i++) {
			T* comp = dynamic_cast<T *>(componentVector[i]);
			if (comp) {
				result.push_back(comp);
			}
		}
		return result;
	};

	template <typename T>
	T* AddComponent() {
		static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");
		T* newComponent = new T();
		componentVector.push_back(newComponent);
		newComponent->gameObject = this;
		newComponent->OnAddedToGameObject();
		return newComponent;
	};

	void SetActive(bool active);
	inline Scene* GetScene();

	//virtual functions to call for inherited classes
	virtual void OnInstantiated() {};
	virtual void Start() {};
	virtual void FixedUpdate(float32 deltaTime) {};
	virtual void OnRender() {};
	virtual void OnGUI() {};
	virtual void OnDestroyed() {};

	//need to be implemented
	virtual void OnCollisionEnter(CollisionInfo2D collision) {};
	virtual void OnCollisionExit(CollisionInfo2D collision) {};
	//virtual void OnTriggerEnter() {};
	//virtual void OnTriggerExit() {};

	string name;


protected:

	GameObject();


private:
	friend class Scene;
	
	void InnerFixedUpdate(float32 deltaTime);
	void Render();
	void RenderGUI();

	vector<Component *> componentVector;
	Transform transform;
	Scene* scene;
	GameObject* prev = nullptr;
	GameObject* next = nullptr;

	bool started = false;
	bool active = true;
};


inline Transform* GameObject::GetTransform() {
	return &transform;
};
inline const Transform* GameObject::GetTransform() const {
	&transform;
};

inline Scene* GameObject::GetScene() {
	return scene;
};
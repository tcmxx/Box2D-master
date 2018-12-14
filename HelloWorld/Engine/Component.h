#pragma once

//#include "GameObject.h"
class GameObject;

class Component
{
	
public:
	//Component(GameObject* gameObject);
	Component();
	~Component();

	GameObject* GetGameObject() const;
	void SetSelfEnabled(bool enabled);

	virtual void OnAddedToGameObject() = 0;
	virtual void Start() {};
	virtual void OnEnabled() {};
	virtual void OnDisabled() {};
	virtual void FixedUpdate(float fixedDeltaTime) {};
	virtual void OnDestroyed() {};
	virtual void OnRender() {};

protected:
	friend class GameObject;
	GameObject * gameObject;
private:
	bool selfEnabled = true;
};


inline GameObject* Component::GetGameObject() const {
	return gameObject;
};


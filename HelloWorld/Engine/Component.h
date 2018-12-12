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


	virtual void OnAddedToGameObject() = 0;
	virtual void Start() {};
	virtual void OnSetActive(bool active) {};	//for now only use this one instead of onenble and ondisable
	virtual void FixedUpdate(float fixedDeltaTime) {};
	virtual void OnDestroyed() {};
	virtual void OnRender() {};

protected:
	friend class GameObject;
	GameObject * gameObject;


};


inline GameObject* Component::GetGameObject() const {
	return gameObject;
};


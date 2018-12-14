#pragma once

#include "GameObject.h"
#include <vector>
#include "Time.h"
#include "Physics2D.h"

using namespace std;




class Scene {

public:
	Scene(float tickRate);
	~Scene();

	//mark the gameobject to be destroyed at the next fixed update.
	void Destroy(GameObject* gameObject);

	//this is dangerous because if might cause issues in physics simulation if this is called in phsyics callbacks.
	void DestroyGameObjectImmediately(GameObject* gameObject);
	void FixedUpdate();

	Physics2D* GetPhysics2D();
	GameTime* GetTime();

	//-------------------------------------------------------------
	//---------------Instantiation functions----------------------
	//-------------------------------------------------------------
	template <typename T>
	T* InstantiateGameObject(const b2Vec2 &p, float32 angle, string name, SerializedGameObjectData*  gameObjectData = nullptr) {
		static_assert(std::is_base_of<GameObject, T>::value, "T must derive from GameObject");
		
		T* newObj = new T();
		newObj->name = name;
		Transform* trans = newObj->GetTransform();
		trans->SetAngle(angle);
		trans->SetPosition(p);

		newObj->scene = this;

		newObj->prev = gameObjectLast;
		newObj->next = nullptr;

		if (gameObjectLast != nullptr) {
			gameObjectLast->next = newObj;
		}
		gameObjectLast = newObj;

		if (gameObjectFirst == nullptr) {
			gameObjectFirst = newObj;
		}

		newObj->Construct(gameObjectData);
		return newObj;
	};
	template <typename T>
	T* InstantiateGameObject(SerializedGameObjectData* gameObjectData = nullptr) {
		return InstantiateGameObject<T>(b2Vec2_zero, 0, "GameObject", gameObjectData);
	}
	template <typename T>
	T* InstantiateGameObject(string name, SerializedGameObjectData* gameObjectData = nullptr) {
		return InstantiateGameObject<T>(b2Vec2_zero, 0, name, gameObjectData);
	}
	template <typename T>
	T* InstantiateGameObject(const b2Vec2 &p, float32 angle, SerializedGameObjectData* gameObjectData = nullptr) {
		return InstantiateGameObject<T>(p, angle, "GameObject", gameObjectData);
	}
	//---------------------------------------------------------
	//-------------------------------------------------------------
	//-------------------------------------------------------------


private:
	friend class Engine;

	GameTime gameTime;

	Physics2D physics2D;

	//right now just use linked list to storeall GameObjects
	GameObject* gameObjectFirst = nullptr;
	GameObject* gameObjectLast = nullptr;
};


inline Physics2D* Scene::GetPhysics2D() {
	return &physics2D;
}

inline GameTime* Scene::GetTime() {
	return &gameTime;
}
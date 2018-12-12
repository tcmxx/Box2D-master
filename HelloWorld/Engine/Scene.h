#pragma once

#include "GameObject.h"
#include <vector>
#include "Time.h"
using namespace std;


//for now the settings are defined here
struct Physics2DSetting {
	int32 velocityIterations = 6;
	int32 positionIterations = 2;
};


class Scene {

public:
	Scene(float tickRate);
	~Scene();



	template <typename T>
	T* InstantiateGameObject(const b2Vec2 &p, float32 angle) {
		static_assert(std::is_base_of<GameObject, T>::value, "T must derive from GameObject");
		
		T* newObj = new T();
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

		newObj->OnInstantiated();
		return newObj;
	};
	template <typename T>
	T* InstantiateGameObject() {
		return InstantiateGameObject<T>(b2Vec2_zero, 0);
	}

	//mark the gameobject to be destroyed at the next fixed update.
	//void Destroy(GameObject* gameObject);

	void DestroyGameObjectImmediately(GameObject* gameObject);
	void FixedUpdate();

	b2World* GetWorld2D();
	void SetGravity(b2Vec2 gravity);

private:
	GameTime gameTime;
	// Define the gravity vector.
	const b2Vec2 DEFAULT_GRAVITY = b2Vec2(0.0f, -10.0f);


	// physics a world object, which will hold and simulate the rigid bodies.
	b2World world2D;
	Physics2DSetting physics2DSetting;

	//right now just use linked list to storeall GameObjects
	GameObject* gameObjectFirst = nullptr;
	GameObject* gameObjectLast = nullptr;
};


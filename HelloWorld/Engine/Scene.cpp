#include "Scene.h"

Scene::Scene(float tickRate):gameTime(tickRate)
{
	
}


Scene::~Scene()
{
	GameObject* currentObj = gameObjectFirst;
	while (currentObj != nullptr) {
		GameObject* tempPtr = currentObj;
		currentObj = currentObj->next;
		delete tempPtr;
	}
}

void Scene::Destroy(GameObject* gameObject) {
	gameObject->SetActive(false);
	gameObject->destroyed = true;
}

void Scene::DestroyGameObjectImmediately(GameObject* gameObject) {

	gameObject->OnDestroyed();
	if (gameObject->next == nullptr && gameObject->prev == nullptr) {
		gameObjectLast = nullptr;
		gameObjectFirst = nullptr;
		delete gameObject;
	}
	else if (gameObject->next == nullptr) {
		gameObjectLast = gameObject->prev;
		gameObjectLast->next = nullptr;
		delete gameObject;
	}
	else if (gameObject->prev == nullptr) {
		gameObjectFirst = gameObject->next;
		gameObjectFirst->prev = nullptr;
		delete gameObject;
	}
	else {
		gameObject->prev->next = gameObject->next;
		gameObject->next->prev = gameObject->prev;
		delete gameObject;
	}
}


void Scene::FixedUpdate() {
	
	float32 interval = gameTime.GetTickInterval();

	//destroy objects
	GameObject* currentObj = gameObjectFirst;
	while (currentObj != nullptr) {
		if (currentObj->destroyed) {
			GameObject* ojb = currentObj;
			currentObj = currentObj->next;
			DestroyGameObjectImmediately(ojb);
		}
		else {
			currentObj = currentObj->next;
		}
	}

	physics2D.Step();

	//step the game objects
	currentObj = gameObjectFirst;
	while (currentObj != nullptr) {
		currentObj->InnerFixedUpdate(interval);
		currentObj = currentObj->next;
	}

	//render all game objects
	currentObj = gameObjectFirst;
	while (currentObj != nullptr) {
		currentObj->Render();
		currentObj = currentObj->next;
	}

	//call all OnGUI
	currentObj = gameObjectFirst;
	while (currentObj != nullptr) {
		currentObj->RenderGUI();
		currentObj = currentObj->next;
	}

	gameTime.tick++;
}


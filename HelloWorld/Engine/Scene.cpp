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
	}
	else if (gameObject->prev != nullptr) {
		gameObjectFirst = gameObject->next;
		gameObjectFirst->prev = nullptr;
	}
	else {
		gameObject->prev->next = gameObject->next;
		gameObject->next->prev = gameObject->prev;
	}
}


void Scene::FixedUpdate() {
	
	float32 interval = gameTime.GetTickInterval();

	physics2D.Step();

	//step the game objects
	GameObject* currentObj = gameObjectFirst;
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


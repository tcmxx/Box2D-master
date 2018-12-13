#include "GameObject.h"
#include "Scene.h"


GameObject::GameObject()
{
	name = "GameObject";
}


GameObject::~GameObject()
{
	
	for (std::vector<Component*>::size_type i = 0; i != componentVector.size(); i++) {
		componentVector[i]->OnDestroyed();
		delete componentVector[i];
	}
	OnDestroyed();
}

void GameObject::SetActive(bool active) {
	this->active = active;
}

void GameObject::InnerFixedUpdate(float32 deltaTime) {
	//TODO this should loop throw all the compoennet and call fixed update
	if (!started && active) {
		started = true;
		//loop through all the components
		for (std::vector<Component*>::size_type i = 0; i != componentVector.size(); i++) {
			componentVector[i]->Start();
		}
		Start();
	}

	if (active) {
		//loop through all the components
		for (std::vector<Component*>::size_type i = 0; i != componentVector.size(); i++) {
			componentVector[i]->FixedUpdate(deltaTime);
		}
		FixedUpdate(deltaTime);
	}

}

void GameObject::Render() {
	if (active) {
		for (std::vector<Component*>::size_type i = 0; i != componentVector.size(); i++) {
			componentVector[i]->OnRender();
		}
		OnRender();
	}
}
void GameObject::RenderGUI() {
	if (active) {
		OnGUI();
	}
}
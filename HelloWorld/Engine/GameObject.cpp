#include "GameObject.h"
#include "Scene.h"


GameObject::GameObject()
{
	name = "GameObject";
}


GameObject::~GameObject()
{
	
	for (std::vector<Component*>::size_type i = 0; i != componentVector.size(); i++) {
		if (active && componentVector[i]->selfEnabled)
			componentVector[i]->OnDisabled();
		componentVector[i]->OnDestroyed();
		delete componentVector[i];
	}
	OnDestroyed();
}

void GameObject::SetActive(bool active) {
	if (started) {
		if (this->active && !active) {
			for (std::vector<Component*>::size_type i = 0; i != componentVector.size(); i++) {
				if (componentVector[i]->selfEnabled)
					componentVector[i]->OnDisabled();
			}
		}
		else if (!this->active && active) {
			for (std::vector<Component*>::size_type i = 0; i != componentVector.size(); i++) {
				if (componentVector[i]->selfEnabled)
					componentVector[i]->OnEnabled();
			}
		}
	}
	this->active = active;
}

void GameObject::InnerFixedUpdate(float32 deltaTime) {
	//TODO this should loop throw all the compoennet and call fixed update
	if (!started && active) {
		started = true;
		//loop through all the components
		for (std::vector<Component*>::size_type i = 0; i != componentVector.size(); i++) {
				componentVector[i]->Start();
				if (componentVector[i]->selfEnabled)
					componentVector[i]->OnEnabled();
		}
		Start();
	}

	if (active) {
		//loop through all the components
		for (std::vector<Component*>::size_type i = 0; i != componentVector.size(); i++) {
			if (componentVector[i]->selfEnabled)
				componentVector[i]->FixedUpdate(deltaTime);
		}
		FixedUpdate(deltaTime);
	}

}

void GameObject::Render() {
	if (active) {
		for (std::vector<Component*>::size_type i = 0; i != componentVector.size(); i++) {
			if (componentVector[i]->selfEnabled)
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
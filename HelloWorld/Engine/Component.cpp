#include "Component.h"
#include "GameObject.h"


Component::Component()
{
}


Component::~Component()
{
}


void Component::SetSelfEnabled(bool enabled) {
	if (gameObject->IsActive()) {
		if (enabled && !selfEnabled) {
			OnEnabled();
		}
		else if (!enabled && selfEnabled) {
			OnDisabled();
		}
	}
	selfEnabled = enabled;
}
#include "Collider2D.h"
//#include "Box2D\Box2D.h"
#include "GameObject.h"
#include "Scene.h"
#include "Rigidbody2D.h"


void Collider2D::SetDensity(float32 density) {
	if (fixture == nullptr) {
		fixtureDef.density = density;
	}
	else {
		fixture->SetDensity(density);
	}
}
void Collider2D::SetFriction(float32 friction) {
	if (fixture == nullptr) {
		fixtureDef.friction = friction;
	}
	else {
		fixture->SetFriction(friction);
	}
}
void Collider2D::SetRestitution(float32 restitution) {
	if (fixture == nullptr) {
		fixtureDef.restitution = restitution;
	}
	else {
		fixture->SetRestitution(restitution);
	}
}
void Collider2D::SetIsSensor(bool isSensor) {
	if (fixture == nullptr) {
		fixtureDef.isSensor = isSensor;
	}
	else {
		fixture->SetSensor(isSensor);
	}
}
void Collider2D::SetFilter(const b2Filter &filter) {
	if (fixture == nullptr) {
		fixtureDef.filter = filter;
	}
	else {
		fixture->SetFilterData(filter);
	}
}



void Collider2D::OnAddedToGameObject() {
	//add the existing collider shapes to the rigid body
	auto body = gameObject->GetComponent<Rigidbody2D>();
	if (body != nullptr) {
		throw  std::exception("Can not change shape after rigid body attached");
	}
}




void Collider2D::Start() {
};
void Collider2D::FixedUpdate(float fixedDeltaTime) {
};
void Collider2D::OnDestroyed() {
};
void Collider2D::OnRender() {
};
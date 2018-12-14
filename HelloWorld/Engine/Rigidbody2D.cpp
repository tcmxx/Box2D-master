#include "Rigidbody2D.h"
#include "GameObject.h"
#include "Scene.h"
#include "Collider2D.h"

void Rigidbody2D::OnAddedToGameObject() {
	Scene* scene = gameObject->GetScene();
	Transform* currentTrans = gameObject->GetTransform();
	//auto world = scene->physics2D.GetWorld2D();
	auto world = scene->GetPhysics2D()->GetWorld2D();
	body = world->CreateBody(&bodyDef);
	body->SetTransform(currentTrans->GetPosition(), currentTrans->GetAngle());
	//add the existing collider shapes to the rigid body
	auto colliders = gameObject->GetComponents<Collider2D>();

	for (std::vector<Collider2D*>::size_type i = 0; i != colliders.size(); i++) {
		RegisterCollider2D(colliders[i]);
	}
}


void Rigidbody2D::RegisterCollider2D(Collider2D* collider) {
	collider->fixtureDef.shape = &(collider->GetShape());
	collider->fixture = body->CreateFixture(&(collider->fixtureDef));
	collider->fixture->SetUserData(collider);
	collider->body = this;
}


b2BodyType Rigidbody2D::GetType() const {
	if (body != nullptr) {
		return body->GetType();
	}
	else {
		return bodyDef.type;
	}
}
void Rigidbody2D::SetType(b2BodyType t) {
	if (body != nullptr) {
		body->SetType(t);
	}
	else {
		bodyDef.type = t;
	}
}

const b2Transform Rigidbody2D::GetTransform() const {
	if (body != nullptr) {
		return body->GetTransform();
	}
	else {
		b2Transform result;
		result.Set(bodyDef.position, bodyDef.angle);
		return result;
	}
}
void Rigidbody2D::SetTransform(const b2Vec2 &p, float32 angle) {
	if (body != nullptr) {
		body->SetTransform(p, angle);
	}
	else {
		bodyDef.position = p;
		bodyDef.angle = angle;
	}
}

const b2Vec2 Rigidbody2D::GetLinearVelocity() const{
	if (body != nullptr) {
		return body->GetLinearVelocity();
	}
	else {
		return bodyDef.linearVelocity;
	}
}
void Rigidbody2D::SetLinearVelocity(b2Vec2 v) {
	if (body != nullptr) {
		body->SetLinearVelocity(v);
	}
	else {
		bodyDef.linearVelocity = v;
	}
}

const float32 Rigidbody2D::GetAngularVelocity() const {
	if (body != nullptr) {
		return body->GetAngularVelocity();
	}
	else {
		return bodyDef.angularVelocity;
	}
}
void Rigidbody2D::SetAngularVelocity(float32 v) {
	if (body != nullptr) {
		body->SetAngularVelocity(v);
	}
	else {
		bodyDef.angularVelocity = v;
	}
}

const float32 Rigidbody2D::GetLinearDamping() const {
	if (body != nullptr) {
		return body->GetLinearDamping();
	}
	else {
		return bodyDef.linearDamping;
	}
}
void Rigidbody2D::SetLinearDamping(float32 d) {
	
	if (body != nullptr) {
		body->SetLinearDamping(d);
	}
	else {
		bodyDef.linearDamping = d;
	}
}

const float32 Rigidbody2D::GetAngularDamping() const {
	if (body != nullptr) {
		return body->GetAngularDamping();
	}
	else {
		return bodyDef.angularDamping;
	}
}
void Rigidbody2D::SetAngularDamping(float32 d) {
	if (body != nullptr) {
		body->SetAngularDamping(d);
	}
	else {
		bodyDef.angularDamping = d;
	}
}


void Rigidbody2D::AddForce(const b2Vec2& force) {
	if (body != nullptr) {
		body->ApplyForceToCenter(force,true);
	}
}

void Rigidbody2D::AddImpulse(const b2Vec2& impulse) {
	if (body != nullptr) {
		body->ApplyLinearImpulseToCenter(impulse, true);
	}
}

void Rigidbody2D::AddTorque(float32 torque) {
	if (body != nullptr) {
		body->ApplyTorque(torque, true);
	}
}




void Rigidbody2D::OnEnabled() {
	if (body != nullptr) {
		body->SetActive(true);
	}
	else {
		bodyDef.active = true;
	}
}
void Rigidbody2D::OnDisabled() {
	if (body != nullptr) {
		//body->SetActive(false);//temperate not doing this now.
		//TODO:need to make on collision callbacks happen out side of physics simulation
	}
	else {
		bodyDef.active = false;
	}
}
void Rigidbody2D::Start() {
};
void Rigidbody2D::FixedUpdate(float fixedDeltaTime) {
	auto bodyTrans = GetTransform();
	auto trans = gameObject->GetTransform();
	trans->SetRotation(bodyTrans.q);
	trans->SetPosition(bodyTrans.p);
};
void Rigidbody2D::OnDestroyed() {
	body->GetWorld()->DestroyBody(body);
};
void Rigidbody2D::OnRender() {
};
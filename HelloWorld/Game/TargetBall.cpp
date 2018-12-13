#include "TargetBall.h"

#include "HelloWorld\Engine\Engine.h"

#include <string>
#include <iostream>

void TargetBall::OnInstantiated() {


	auto collider = AddComponent<CircleCollider2D>();
	collider->SetCircle(DEFAULT_RADIUS, b2Vec2_zero);
	collider->SetRestitution(DEFAULT_RESTITUTION);
	collider->SetDensity(DEFAULT_DENSITY);
	collider->SetFriction(DEFAULT_FRICTION);

	Rigidbody2D* body = AddComponent<Rigidbody2D>();
	body->SetType(b2_dynamicBody);

	debugDraw = Engine::GetDebugDraw();
}



void TargetBall::OnRender() {
	debugDraw->DrawCircle(GetTransform()->GetPosition(),DEFAULT_RADIUS, b2Color(1,0,0,1));
}


void TargetBall::OnCollisionEnter(CollisionInfo2D collision) {
	auto position = collision.other->GetGameObject()->name;
	printf("Collision Enter: %s\n", position.c_str());

};
void TargetBall::OnCollisionExit(CollisionInfo2D collision) {

};
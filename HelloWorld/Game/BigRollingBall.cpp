#include "BigRollingBall.h"

#include "HelloWorld\Engine\Engine.h"

#include <string>
#include <iostream>

void BigRollingBall::Construct(SerializedGameObjectData* data) {
	time = GetScene()->GetTime();
	debugDraw = Engine::GetDebugDraw();
}

void BigRollingBall::InitializeWithCommand(PlayerCommand command) {
	GetTransform()->SetPosition(command.usePosition);
	tickToEffect = command.effectDelay + command.useTick;
	tickToDestroy = tickToEffect + LIVE_TICKS;
}


void BigRollingBall::AddPhysics() {
	if (hasPhysics)
		return;
	hasPhysics = true;
	auto collider = AddComponent<CircleCollider2D>();
	collider->SetCircle(DEFAULT_RADIUS, b2Vec2_zero);
	collider->SetRestitution(DEFAULT_RESTITUTION);
	collider->SetDensity(DEFAULT_DENSITY);
	collider->SetFriction(DEFAULT_FRICTION);

	body = AddComponent<Rigidbody2D>();
	body->SetType(b2_dynamicBody);
	body->SetAngularDamping(0.1f);
	body->SetLinearDamping(0.5f);
	debugDraw = Engine::GetDebugDraw();
}

void BigRollingBall::OnRender() {
	auto rot = GetTransform()->GetRotation();
	b2Color color = playerIndex == 0 ? b2Color(0, 1, 0, 1) : b2Color(0, 0, 1, 1);
	if(hasPhysics)
		debugDraw->DrawSolidCircle(GetTransform()->GetPosition(),DEFAULT_RADIUS, rot.GetXAxis(), color);
	else
		debugDraw->DrawCircle(GetTransform()->GetPosition(), DEFAULT_RADIUS, color);
}

void BigRollingBall::FixedUpdate(float32 deltaTime) {
	if (time->tick == tickToEffect) {
		AddPhysics();
	}
	if (time->tick == tickToDestroy) {
		GetScene()->Destroy(this);
	}

	if (playerIndex == 0) {
		if (hasPhysics) {
			body->AddTorque(-ROTATION_TORQUE);
		}
	}
	else {
		if (hasPhysics) {
			body->AddTorque(ROTATION_TORQUE);
		}
	}
}


void BigRollingBall::OnCollisionEnter(CollisionInfo2D collision) {
	//auto position = collision.other->GetGameObject()->name;
	//printf("Collision Enter: %s\n", position.c_str());

};
void BigRollingBall::OnCollisionExit(CollisionInfo2D collision) {

};
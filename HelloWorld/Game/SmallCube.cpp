#include "SmallCube.h"

#include "HelloWorld\Engine\Engine.h"

#include <string>
#include <iostream>

void SmallCube::Construct(SerializedGameObjectData* data) {
	time = GetScene()->GetTime();
	debugDraw = Engine::GetDebugDraw();
}

void SmallCube::InitializeWithCommand(PlayerCommand command) {
	GetTransform()->SetPosition(command.usePosition);
	tickToEffect = command.effectDelay + command.useTick;
	tickToDestroy = tickToEffect + LIVE_TICKS;
	playerIndex = command.playerIndex;

}


void SmallCube::AddPhysics() {
	if (hasPhysics)
		return;
	hasPhysics = true;
	auto collider = AddComponent<BoxCollider2D>();
	collider->SetBox(DEFAULT_SIZE, b2Vec2_zero, 0);
	collider->SetRestitution(DEFAULT_RESTITUTION);
	collider->SetDensity(DEFAULT_DENSITY);
	collider->SetFriction(DEFAULT_FRICTION);

	body = AddComponent<Rigidbody2D>();
	body->SetType(b2_dynamicBody);
	body->SetAngularDamping(0.1f);
	body->SetLinearDamping(0.5f);
	debugDraw = Engine::GetDebugDraw();
}

void SmallCube::OnRender() {
	auto rot = GetTransform()->GetRotation();
	b2Color color = playerIndex == 0 ? b2Color(0, 0.7f, 0, 1) : b2Color(0, 0, 0.7f, 1);
	if (hasPhysics)
		debugDraw->DrawSolidBox(DEFAULT_SIZE, b2Vec2_zero, color, GetTransform()->GetBaseTransform());
	else
		debugDraw->DrawBox(DEFAULT_SIZE, b2Vec2_zero, color, GetTransform()->GetBaseTransform());
}

void SmallCube::FixedUpdate(float32 deltaTime) {
	if (time->tick == tickToEffect) {
		AddPhysics();
	}
	if (time->tick == tickToDestroy) {
		GetScene()->Destroy(this);
	}
}


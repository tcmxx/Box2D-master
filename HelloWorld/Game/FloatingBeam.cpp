#include "FloatingBeam.h"

#include "HelloWorld\Engine\Engine.h"

#include <string>
#include <iostream>

void FloatingBeam::Construct(SerializedGameObjectData* data) {
	time = GetScene()->GetTime();
	debugDraw = Engine::GetDebugDraw();
}

void FloatingBeam::InitializeWithCommand(PlayerCommand command) {
	GetTransform()->SetPosition(command.usePosition);
	tickToEffect = command.effectDelay + command.useTick;
	tickToDestroy = tickToEffect + LIVE_TICKS;
	playerIndex = command.playerIndex;

	GetTransform()->SetAngle(playerIndex == 0 ? DEFAULT_ANGLE : -DEFAULT_ANGLE);
}


void FloatingBeam::AddPhysics() {
	if (hasPhysics)
		return;
	hasPhysics = true;
	auto collider = AddComponent<BoxCollider2D>();
	collider->SetBox(DEFAULT_SIZE, b2Vec2_zero,0);
	collider->SetRestitution(DEFAULT_RESTITUTION);
	collider->SetDensity(DEFAULT_DENSITY);
	collider->SetFriction(DEFAULT_FRICTION);

	body = AddComponent<Rigidbody2D>();
	body->SetType(b2_staticBody);
	body->SetAngularDamping(0.1f);
	body->SetLinearDamping(0.5f);
	debugDraw = Engine::GetDebugDraw();
}

void FloatingBeam::OnRender() {
	auto rot = GetTransform()->GetRotation();
	b2Color color = playerIndex == 0 ? b2Color(0, 1, 0, 1) : b2Color(0, 0, 1, 1);
	if (hasPhysics)
		debugDraw->DrawSolidBox(DEFAULT_SIZE, b2Vec2_zero, color, GetTransform()->GetBaseTransform());
	else
		debugDraw->DrawBox(DEFAULT_SIZE, b2Vec2_zero, color, GetTransform()->GetBaseTransform());
}

void FloatingBeam::FixedUpdate(float32 deltaTime) {
	if (time->tick == tickToEffect) {
		AddPhysics();
	}
	if (time->tick == tickToDestroy) {
		GetScene()->Destroy(this);
	}
}


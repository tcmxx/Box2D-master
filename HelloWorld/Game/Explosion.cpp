#include "Explosion.h"

#include "HelloWorld\Engine\Engine.h"

#include <string>
#include <iostream>

void Explosion::Construct(SerializedGameObjectData* data) {
	time = GetScene()->GetTime();
	debugDraw = Engine::GetDebugDraw();
}

void Explosion::InitializeWithCommand(PlayerCommand command) {
	GetTransform()->SetPosition(command.usePosition);
	tickToEffect = command.effectDelay + command.useTick;
	tickToDestroy = tickToEffect + LIVE_TICKS;
	playerIndex = command.playerIndex;
}


void Explosion::Explode() {
	if (exploded)
		return;
	exploded = true;
	std::vector<Collider2D*>colliders = GetScene()->GetPhysics2D()->SphereOverlay(GetTransform()->GetPosition(), EXPLOSION_RADIUS);

	b2Vec2 mCenter = GetTransform()->GetPosition();

	for (std::vector<Collider2D*>::size_type i = 0; i != colliders.size(); i++) {
		Rigidbody2D* body = colliders[i]->GetBody();
		Transform* transform = colliders[i]->GetGameObject()->GetTransform();
		b2Vec2 center = transform->GetPosition();
		if (body != nullptr) {
			auto dir = (center - mCenter);
			dir.Normalize();
			dir.x *= EXPLOSION_IMPULSE;
			dir.y *= EXPLOSION_IMPULSE;
			body->AddImpulse(dir);
		}
	}
}

void Explosion::OnRender() {
	auto rot = GetTransform()->GetRotation();
	b2Color color = playerIndex == 0 ? b2Color(0, 1, 0, 1) : b2Color(0, 0, 1, 1);
	if (exploded)
		debugDraw->DrawSolidCircle(GetTransform()->GetPosition(), EXPLOSION_RADIUS, b2Vec2_zero, color);
	else
		debugDraw->DrawCircle(GetTransform()->GetPosition(), MARK_RADIUS, color);
}

void Explosion::FixedUpdate(float32 deltaTime) {
	if (time->tick == tickToEffect) {
		Explode();
	}
	if (time->tick == tickToDestroy) {
		GetScene()->Destroy(this);
	}
}

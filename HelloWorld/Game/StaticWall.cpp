#include "StaticWall.h"

#include "HelloWorld\Engine\Engine.h"

#include <string>
#include <iostream>

void StaticWall::Construct(SerializedGameObjectData* data) {

	StaticWallData* wallData = (StaticWallData*)(data);
	bool hasData = (wallData != nullptr);
	if (!hasData) {
		wallData = new StaticWallData();
	}
	b2Vec2 size = wallData->size;
	float32 rest = wallData->restitution;
	float32 fric = wallData->friction;

	collider = AddComponent<BoxCollider2D>();
	collider->SetBox(size, b2Vec2_zero, 0);
	collider->SetRestitution(rest);
	collider->SetFriction(fric);
	collider->SetDensity(1);

	Rigidbody2D* body = AddComponent<Rigidbody2D>();
	body->SetType(b2_staticBody);

	debugDraw = Engine::GetDebugDraw();

	if (!hasData)
		delete wallData;
}



void StaticWall::OnRender() {
	debugDraw->DrawSolidBox(collider->GetSize(), collider->GetCenter(), b2Color(1, 0, 0, 1), GetTransform()->GetBaseTransform());
}

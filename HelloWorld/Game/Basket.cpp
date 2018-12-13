#include "Basket.h"

#include "HelloWorld\Engine\Engine.h"
#include "GameController.h"
#include <string>
#include <iostream>

void Basket::Construct(SerializedGameObjectData* data) {

	BasketData* basketData = (BasketData*)(data);
	bool hasData = (basketData != nullptr);
	if (!hasData) {
		basketData = new BasketData();
	}
	isPlayerOne = basketData->isPlayerOne;
	color = basketData->color;
	b2Vec2 size = basketData->size;
	float32 rest = basketData->restitution;
	float32 fric = basketData->friction;

	collider = AddComponent<BoxCollider2D>();
	collider->SetBox(size, b2Vec2_zero, 0);
	collider->SetRestitution(rest);
	collider->SetFriction(fric);

	Rigidbody2D* body = AddComponent<Rigidbody2D>();
	body->SetType(b2_staticBody);

	debugDraw = Engine::GetDebugDraw();

	if (!hasData)
		delete basketData;
}



void Basket::OnRender() {
	debugDraw->DrawSolidBox(collider->GetSize(), collider->GetCenter(), color, GetTransform()->GetBaseTransform());
}


void Basket::OnCollisionEnter(CollisionInfo2D collision)  {
	GameObject* obj = collision.other->GetGameObject();
	if (obj->name == "TargetBall") {
		GameController::GetInstance()->AddPlayerPoint(isPlayerOne);
		GetScene()->Destroy(obj);
	}
}
void Basket::OnCollisionExit(CollisionInfo2D collision) {

}
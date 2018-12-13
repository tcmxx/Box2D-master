#pragma once

#include "HelloWorld\Engine\GameObject.h"
#include "HelloWorld\Engine\BoxCollider2D.h"

class DebugDraw;


class BasketData :public SerializedGameObjectData {
public:
	b2Vec2 size = b2Vec2(2, 1);
	float32 restitution = 0.5f;
	float32 friction = 0.5f;
	b2Color color = b2Color(1,0,0,1);
	bool isPlayerOne = true;
};

class Basket : public GameObject {

public:
	void Construct(SerializedGameObjectData* data) override;
	void OnRender() override;
	void OnCollisionEnter(CollisionInfo2D collision) override;
	void OnCollisionExit(CollisionInfo2D collision) override;

	const string TARGET_NAME = "TargetBall";

protected:
	bool isPlayerOne;
	b2Color color = b2Color(1, 0, 0, 1);
	BoxCollider2D * collider;
	DebugDraw * debugDraw;
};
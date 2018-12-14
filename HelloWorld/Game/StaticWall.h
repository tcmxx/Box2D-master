#pragma once

#include "HelloWorld\Engine\GameObject.h"
#include "HelloWorld\Engine\BoxCollider2D.h"

class DebugDraw;


class StaticWallData :public SerializedGameObjectData{
public:
	b2Vec2 size = b2Vec2(1,1);
	float32 restitution = 0.5f;
	float32 friction = 0.6f;
};

class StaticWall : public GameObject {

public:
	void Construct(SerializedGameObjectData* data) override;
	void OnRender() override;
	void OnCollisionEnter(CollisionInfo2D collision) override {};
	void OnCollisionExit(CollisionInfo2D collision) override {};
protected:

	BoxCollider2D * collider;
	DebugDraw * debugDraw;
};
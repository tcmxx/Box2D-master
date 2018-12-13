#pragma once

#include "Collider2D.h"

class BoxCollider2D :public Collider2D {
public:
	BoxCollider2D();
	void SetBox(const b2Vec2 &size, const b2Vec2 &center, float32 angle);
	b2Vec2 GetSize();
	b2Vec2 GetCenter();
	float32 GetAngle();

	const b2Shape& GetShape()  const override;
	//void OnRender() override;
private:
	b2Vec2 size = b2Vec2(1,1); 
	b2Vec2 center = b2Vec2_zero;
	float32 angle = 0;

	b2PolygonShape shapeInitialShape;
};



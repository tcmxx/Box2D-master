#pragma once

#include "Collider2D.h"

class BoxCollider2D :public Collider2D {
public:
	BoxCollider2D();
	void SetBox(const b2Vec2 &size, const b2Vec2 &center, float32 angle);

	const b2Shape& GetShape()  const override;

private:
	b2PolygonShape shapeInitialShape;
};



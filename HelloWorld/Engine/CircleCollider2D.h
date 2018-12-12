#pragma once

#include "Collider2D.h"

class CircleCollider2D :public Collider2D {
public:
	CircleCollider2D();

	void SetCircle(float radius, b2Vec2 center);

	const b2Shape& GetShape()  const override;

private:
	b2CircleShape shapeInitialShape;
};



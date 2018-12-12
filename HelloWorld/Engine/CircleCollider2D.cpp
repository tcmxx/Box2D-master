#include "CircleCollider2D.h"


CircleCollider2D::CircleCollider2D(){
	shapeInitialShape.m_p.SetZero();
	shapeInitialShape.m_radius = 1;
}

void CircleCollider2D::SetCircle(float radius, b2Vec2 center) {
	if (fixture != nullptr) {
		throw  std::exception("Can not change shape after rigid body attached");
	}
	else {
		shapeInitialShape.m_radius = radius;
		shapeInitialShape.m_p = center;
	}
}

const b2Shape& CircleCollider2D::GetShape()  const {
	return shapeInitialShape;
}
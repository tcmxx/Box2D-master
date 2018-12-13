#include "BoxCollider2D.h"




BoxCollider2D::BoxCollider2D() {
	shapeInitialShape.SetAsBox(1.0f,1.0f,b2Vec2_zero,0);
}


void BoxCollider2D::SetBox(const b2Vec2 &size, const b2Vec2 &center, float32 angle) {
	if (fixture != nullptr) {
		throw  std::exception("Can not change shape after rigid body attached");
	}
	else {
		shapeInitialShape.SetAsBox(size.x, size.y, center, angle);
		this->size = size;
		this->center = center;
		this->angle = angle;
	}
}

b2Vec2 BoxCollider2D::GetSize() {
	return size;
}
b2Vec2 BoxCollider2D::GetCenter() {
	return center;
}
float32 BoxCollider2D::GetAngle() {
	return angle;
}


const b2Shape& BoxCollider2D::GetShape()  const {
	return shapeInitialShape;
}
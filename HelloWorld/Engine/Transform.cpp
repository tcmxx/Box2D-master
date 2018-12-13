#include "Transform.h"



Transform::Transform()
{
}


Transform::~Transform()
{
}


b2Vec2 Transform::TransformPoint(const b2Vec2& position) const {
	return b2Mul(baseTransform, position);
}
b2Vec2 Transform::InverseTransformPoint(const b2Vec2& position) const {
	return b2MulT(baseTransform, position);
}

b2Vec2 Transform::TransformVector(const b2Vec2& vector) const {
	return b2Mul(baseTransform.q, vector);
}
b2Vec2 Transform::InverseTransformVector(const b2Vec2& vector) const {
	return b2MulT(baseTransform.q, vector);
}

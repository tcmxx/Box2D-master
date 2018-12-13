#pragma once

#include "Box2D\Box2D.h"
#include <vector>

///Transfrom implementation.
///It does not have scaling related right now.
class Transform
{
public:
	Transform();
	~Transform();

	void SetPosition(const b2Vec2& position);
	void SetRotation(const b2Rot& rotation);
	void SetAngle(const float32 angle);

	b2Vec2 TransformPoint(const b2Vec2& position) const;
	b2Vec2 InverseTransformPoint(const b2Vec2& position) const;

	b2Vec2 TransformVector(const b2Vec2& vector) const;
	b2Vec2 InverseTransformVector(const b2Vec2& vector) const;

	b2Transform GetBaseTransform() const;

	const b2Vec2& GetPosition() const;
	const b2Rot& GetRotation() const;
	const float32 GetAngle() const;

private:
	b2Transform baseTransform;

	///children of the transform. Current not in use...
	std::vector<Transform*> children;	
};

inline void Transform::SetPosition(const b2Vec2& position) {
	baseTransform.p = position;
}
inline void Transform::SetRotation(const b2Rot& rotation) {
	baseTransform.q = rotation;
}
inline void Transform::SetAngle(const float32 angle) {
	baseTransform.q.Set(angle);
}

inline const b2Vec2& Transform::GetPosition() const {
	return baseTransform.p;
};
inline const b2Rot& Transform::GetRotation() const {
	return baseTransform.q;
};
inline const float32 Transform::GetAngle() const {
	return baseTransform.q.GetAngle();
};

inline b2Transform Transform:: GetBaseTransform() const {
	return baseTransform;
};
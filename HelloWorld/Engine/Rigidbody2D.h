#pragma once
#include "Component.h"

#include "Box2D\Box2D.h"

class Rigidbody2D :public Component {
public:

	b2BodyType GetType() const;
	void SetType(b2BodyType t);

	const b2Transform GetTransform() const;
	void SetTransform(const b2Vec2 &p, float32 angle);

	const b2Vec2 GetLinearVelocity() const;
	void SetLinearVelocity(b2Vec2 v);

	const float32 GetAngularVelocity() const;
	void SetAngularVelocity(float32 v);

	const float32 GetLinearDamping() const;
	void SetLinearDamping(float32 d);

	const float32 GetAngularDamping() const;
	void SetAngularDamping(float32 d);

	void AddForce(const b2Vec2& force);
	void AddTorque(float32 torque);
	void AddImpulse(const b2Vec2& impulse);

	void OnAddedToGameObject() override;
	void OnEnabled() override;
	void OnDisabled() override;
	void Start() override;
	void FixedUpdate(float fixedDeltaTime) override;
	void OnDestroyed() override;
	void OnRender() override;
protected:
	friend class Collider2D;
	friend class GameObject;
	void RegisterCollider2D(Collider2D* collider);
private:
	b2BodyDef bodyDef;
	b2Body * body;
};
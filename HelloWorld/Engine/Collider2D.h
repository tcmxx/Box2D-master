#pragma once
#include "Component.h"
#include "Box2D\Box2D.h"
//struct b2FixtureDef;
//class b2Fixture;

class Collider2D :public Component {
public:
	void SetDensity(float32 density);
	void SetFriction(float32 friction);
	void SetRestitution(float32 restitution);
	void SetIsSensor(bool isSensor);
	void SetFilter(const b2Filter &filter);

	bool HasBody();


	void OnAddedToGameObject() override;
	void Start() override;
	void FixedUpdate(float fixedDeltaTime) override;
	void OnDestroyed() override;
	void OnRender() override;

	/// Return the shape for creating the fixture. This is called by the Rigidbody2D
	virtual const b2Shape& GetShape() const = 0;
protected:
	b2Fixture * fixture = nullptr;
private:
	friend class Rigidbody2D;
	b2FixtureDef fixtureDef;

};

inline bool Collider2D::HasBody() {
	return fixture != nullptr;
}
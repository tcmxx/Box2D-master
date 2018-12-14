#pragma once

#include "HelloWorld\Engine\GameObject.h"
#include "PlayerCommand.h"

class DebugDraw;

class BigRollingBall : public GameObject {

public :
	const float32 DEFAULT_RADIUS = 3.0f;
	const float32 DEFAULT_RESTITUTION = 0.5f;
	const float32 DEFAULT_DENSITY = 2.0f;
	const float32 DEFAULT_FRICTION =0.5f;
	const int LIVE_TICKS = 1200;
	const int ROTATION_TORQUE = 500;

	void InitializeWithCommand(PlayerCommand command);

	void FixedUpdate(float32 deltaTime) override;
	void Construct(SerializedGameObjectData* data) override;
	void OnRender() override;
	void OnCollisionEnter(CollisionInfo2D collision) override;
	void OnCollisionExit(CollisionInfo2D collision) override;
protected:

	void AddPhysics();

	Rigidbody2D* body;
	int playerIndex;
	bool hasPhysics = false;
	DebugDraw* debugDraw;
	GameTime* time;
	int tickToEffect;
	int tickToDestroy;
};
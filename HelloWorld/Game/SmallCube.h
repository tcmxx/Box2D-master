#pragma once

#include "HelloWorld\Engine\GameObject.h"
#include "PlayerCommand.h"

class DebugDraw;

class SmallCube : public GameObject {

public:
	const float32 DEFAULT_RESTITUTION = 0.1f;
	const float32 DEFAULT_DENSITY = 15.0f;
	const float32 DEFAULT_FRICTION = 0.5f;
	const b2Vec2 DEFAULT_SIZE = b2Vec2(0.5f, 0.5f);
	const int LIVE_TICKS = 800;

	void InitializeWithCommand(PlayerCommand command);

	void FixedUpdate(float32 deltaTime) override;
	void Construct(SerializedGameObjectData* data) override;
	void OnRender() override;
protected:

	void AddPhysics();

	Rigidbody2D* body;
	int playerIndex;
	DebugDraw* debugDraw;
	GameTime* time;
	int tickToEffect;
	int tickToDestroy;

	bool hasPhysics = false;
};
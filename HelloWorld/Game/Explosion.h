#pragma once

#include "HelloWorld\Engine\GameObject.h"
#include "PlayerCommand.h"

class DebugDraw;

class Explosion : public GameObject {

public:
	const float32 MARK_RADIUS = 0.5f;
	const float32 EXPLOSION_RADIUS = 6.0f;
	const float32 EXPLOSION_IMPULSE = 500;
	const int LIVE_TICKS = 10;

	void InitializeWithCommand(PlayerCommand command);

	void FixedUpdate(float32 deltaTime) override;
	void Construct(SerializedGameObjectData* data) override;
	void OnRender() override;
protected:

	void Explode();

	bool exploded = false;
	int playerIndex;
	DebugDraw* debugDraw;
	GameTime* time;
	int tickToEffect;
	int tickToDestroy;
};
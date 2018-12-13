#pragma once

#include "HelloWorld\Engine\GameObject.h"


class DebugDraw;

class TargetBall : public GameObject {

public :
	const float32 DEFAULT_RADIUS = 2.0f;
	const float32 DEFAULT_RESTITUTION = 0.5f;
	const float32 DEFAULT_DENSITY = 2.0f;
	const float32 DEFAULT_FRICTION = 0.2f;

	void OnInstantiated() override;
	void OnRender() override;
	void OnCollisionEnter(CollisionInfo2D collision) override;
	void OnCollisionExit(CollisionInfo2D collision) override;
protected:


	DebugDraw* debugDraw;
};
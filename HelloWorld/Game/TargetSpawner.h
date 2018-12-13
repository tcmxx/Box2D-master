#pragma once

#include "HelloWorld\Engine\GameObject.h"


class TargetSpawner : public GameObject {

public:
	static TargetSpawner*  GetInstance();

	void Construct(SerializedGameObjectData* data) override;
	void FixedUpdate(float32 deltaTime) override;

	float32 initialDelay = 3;
	float32 spawnInterval = 10;
	b2Vec2 spawnPosition = b2Vec2(0,35);
private:
	static TargetSpawner* instance;
	float32 countDownTimer;
};

inline TargetSpawner*  TargetSpawner::GetInstance() {
	return instance;
}
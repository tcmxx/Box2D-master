#include "TargetSpawner.h"

#include "HelloWorld\Engine\Engine.h"
#include "TargetBall.h"

TargetSpawner* TargetSpawner::instance;

void TargetSpawner::Construct(SerializedGameObjectData* data) {
	instance = this;

	countDownTimer = initialDelay;
}

void TargetSpawner::FixedUpdate(float32 deltaTime) {
	countDownTimer -= deltaTime;
	if (countDownTimer <= 0) {
		countDownTimer = spawnInterval;
		GetScene()->InstantiateGameObject<TargetBall>(spawnPosition, 0, "TargetBall");
	}
	
}

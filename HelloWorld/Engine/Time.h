#pragma once
#include "Box2D\Box2D.h"

using namespace std;

///time related. useful for network compensation and prediction/sync related stuff
///ported from Unity FPSSample project
struct GameTime
{
public:

	GameTime(int tickRate);

	const int GetTickRate() const;
	void SetTickRate(int tickRate);

	const float32 GetTickInterval();

	int tick;
	int tickDuration;

private:
	int mTickRate;
	float tickInterval;
};

inline GameTime::GameTime(int tickRate) {
	mTickRate = tickRate;
	tickInterval = 1.0f / mTickRate;
	tick = 1;
	tickDuration = 0;
};

inline const float32 GameTime::GetTickInterval() {
	return tickInterval;
}

inline const int GameTime::GetTickRate() const {
	return mTickRate;
}

inline void GameTime::SetTickRate(int tickRate) {
	mTickRate = tickRate;
	tickInterval = 1.0f / mTickRate;
}
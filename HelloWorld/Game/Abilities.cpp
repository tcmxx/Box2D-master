#include "Abilities.h"
#include "HelloWorld\Engine\Engine.h"
#include "BigRollingBall.h"
#include "GameController.h"

///-------------------Ability Large Ball--------------------------
b2AABB AbilityLargeBall::GetRange(int playeIndex) {
	b2AABB aabb;
	aabb.lowerBound = b2Vec2(-10, -10);
	aabb.upperBound = b2Vec2(10, 10);
	return aabb;
}
PlayerCommand AbilityLargeBall::GenerateCommand(b2Vec2 position, int playeIndex) {
	PlayerCommand command;
	command.effectDelay = DELAY_TICK;
	command.name = NAME;
	command.usePosition = position;
	command.playerIndex = playeIndex;
	command.useTick = Engine::GetScene()->GetTime()->tick;
	return command;
};
void AbilityLargeBall::ExecuteCommand(PlayerCommand command) {
	BigRollingBall* ball = Engine::GetScene()->InstantiateGameObject<BigRollingBall>(command.usePosition,0,"BigBall");
	ball->InitializeWithCommand(command);
};
///-----------------------------------------------------------------
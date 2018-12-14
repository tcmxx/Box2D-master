#include "Abilities.h"
#include "HelloWorld\Engine\Engine.h"
#include "BigRollingBall.h"
#include "GameController.h"
#include "FloatingBeam.h"
#include "SmallCube.h"
#include "Explosion.h"

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


///-------------------Ability Beam--------------------------
b2AABB AbilityFloatingBeam::GetRange(int playeIndex) {
	b2AABB aabb;
	aabb.lowerBound = b2Vec2(-10, -10);
	aabb.upperBound = b2Vec2(10, 10);
	return aabb;
}
PlayerCommand AbilityFloatingBeam::GenerateCommand(b2Vec2 position, int playeIndex) {
	PlayerCommand command;
	command.effectDelay = DELAY_TICK;
	command.name = NAME;
	command.usePosition = position;
	command.playerIndex = playeIndex;
	command.useTick = Engine::GetScene()->GetTime()->tick;
	return command;
};
void AbilityFloatingBeam::ExecuteCommand(PlayerCommand command) {
	FloatingBeam* beam = Engine::GetScene()->InstantiateGameObject<FloatingBeam>(command.usePosition, 0, "Beam");
	beam->InitializeWithCommand(command);
};
///-----------------------------------------------------------------



///-------------------Ability Small Cube--------------------------
b2AABB AbilitySmallCube::GetRange(int playeIndex) {
	b2AABB aabb;
	aabb.lowerBound = b2Vec2(-10, -10);
	aabb.upperBound = b2Vec2(10, 10);
	return aabb;
}
PlayerCommand AbilitySmallCube::GenerateCommand(b2Vec2 position, int playeIndex) {
	PlayerCommand command;
	command.effectDelay = DELAY_TICK;
	command.name = NAME;
	command.usePosition = position;
	command.playerIndex = playeIndex;
	command.useTick = Engine::GetScene()->GetTime()->tick;
	return command;
};
void AbilitySmallCube::ExecuteCommand(PlayerCommand command) {
	SmallCube* cube = Engine::GetScene()->InstantiateGameObject<SmallCube>(command.usePosition, 0, "SmallCube");
	cube->InitializeWithCommand(command);
};
///-----------------------------------------------------------------

///-------------------Ability Explosion--------------------------
b2AABB AbilityExplosion::GetRange(int playeIndex) {
	b2AABB aabb;
	aabb.lowerBound = b2Vec2(-20, -10);
	aabb.upperBound = b2Vec2(20, 30);
	return aabb;
}
PlayerCommand AbilityExplosion::GenerateCommand(b2Vec2 position, int playeIndex) {
	PlayerCommand command;
	command.effectDelay = DELAY_TICK;
	command.name = NAME;
	command.usePosition = position;
	command.playerIndex = playeIndex;
	command.useTick = Engine::GetScene()->GetTime()->tick;
	return command;
};
void AbilityExplosion::ExecuteCommand(PlayerCommand command) {
	Explosion* exp = Engine::GetScene()->InstantiateGameObject<Explosion>(command.usePosition, 0, "Explosion");
	exp->InitializeWithCommand(command);
};
///-----------------------------------------------------------------

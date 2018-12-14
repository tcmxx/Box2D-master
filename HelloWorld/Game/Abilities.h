#pragma once
#include "Box2D\Box2D.h"
#include "PlayerCommand.h"


class Ability:public PlayerCommandExecuter {
public:
	virtual b2AABB GetRange(int playeIndex) = 0;

	virtual PlayerCommand GenerateCommand(b2Vec2 position, int playeIndex) = 0;
	virtual void ExecuteCommand(PlayerCommand command) = 0 ;
	virtual string GetCommandName() = 0;

	int cooldownTick;
	int manaCost;
};


class AbilityLargeBall :public Ability {
public:
	virtual b2AABB GetRange(int playeIndex);
	virtual PlayerCommand GenerateCommand(b2Vec2 position, int playeIndex)override ;
	virtual void ExecuteCommand(PlayerCommand command) override;
	virtual string GetCommandName() override { return NAME; };
private:
	const int DELAY_TICK = 50;
	const string NAME = "AbilityLargeBall";
};
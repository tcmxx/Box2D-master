#pragma once
#include "Box2D\Box2D.h"
#include "PlayerCommand.h"


class Ability:public PlayerCommandExecuter {
public:
	virtual b2AABB GetRange(int playeIndex) = 0;

	virtual PlayerCommand GenerateCommand(b2Vec2 position, int playeIndex) = 0;
	virtual void ExecuteCommand(PlayerCommand command) = 0 ;
	virtual string GetCommandName() = 0;
	virtual int GetCoolDownTick() = 0;
	virtual int GetManaCost() = 0;

	virtual string GetAbilityName() = 0;
};


class AbilityLargeBall :public Ability {
public:
	virtual b2AABB GetRange(int playeIndex);
	virtual PlayerCommand GenerateCommand(b2Vec2 position, int playeIndex)override ;
	virtual void ExecuteCommand(PlayerCommand command) override;
	virtual string GetCommandName() override { return NAME; };
	virtual int GetCoolDownTick() {return COOLDOWN_TICK;};
	virtual int GetManaCost() {return MANACOST;};
	virtual string GetAbilityName() override { return ABILITY_NAME; };
private:
	const int MANACOST = 4;	//not used yet
	const int COOLDOWN_TICK = 650;
	const int DELAY_TICK = 50;
	const string NAME = "AbilityLargeBall";
	const string ABILITY_NAME = "Large Ball";
};

class AbilityFloatingBeam :public Ability {
public:
	virtual b2AABB GetRange(int playeIndex);
	virtual PlayerCommand GenerateCommand(b2Vec2 position, int playeIndex)override;
	virtual void ExecuteCommand(PlayerCommand command) override;
	virtual string GetCommandName() override { return NAME; };
	virtual int GetCoolDownTick() { return COOLDOWN_TICK; };
	virtual int GetManaCost() { return MANACOST; };
	virtual string GetAbilityName() override { return ABILITY_NAME; };

private:
	const int MANACOST = 4;
	const int COOLDOWN_TICK = 650;
	const int DELAY_TICK = 50;
	const string NAME = "AbilityFloatingBeam";
	const string ABILITY_NAME = "Floating Beam";
};


class AbilitySmallCube :public Ability {
public:
	virtual b2AABB GetRange(int playeIndex);
	virtual PlayerCommand GenerateCommand(b2Vec2 position, int playeIndex)override;
	virtual void ExecuteCommand(PlayerCommand command) override;
	virtual string GetCommandName() override { return NAME; };
	virtual int GetCoolDownTick() { return COOLDOWN_TICK; };
	virtual int GetManaCost() { return MANACOST; };
	virtual string GetAbilityName() override { return ABILITY_NAME; };

private:
	const int MANACOST = 1;
	const int COOLDOWN_TICK = 800;
	const int DELAY_TICK = 50;
	const string NAME = "AbilitySmallCube";
	const string ABILITY_NAME = "Small Cube";
};


class AbilityExplosion :public Ability {
public:
	virtual b2AABB GetRange(int playeIndex);
	virtual PlayerCommand GenerateCommand(b2Vec2 position, int playeIndex)override;
	virtual void ExecuteCommand(PlayerCommand command) override;
	virtual string GetCommandName() override { return NAME; };
	virtual int GetCoolDownTick() { return COOLDOWN_TICK; };
	virtual int GetManaCost() { return MANACOST; };
	virtual string GetAbilityName() override { return ABILITY_NAME; };

private:
	const int MANACOST = 4;
	const int COOLDOWN_TICK = 250;
	const int DELAY_TICK = 50;
	const string NAME = "Explosion";
	const string ABILITY_NAME = "Explosion";
};
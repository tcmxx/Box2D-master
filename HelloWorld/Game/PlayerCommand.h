#pragma once
#include <string>
#include "Box2D\Box2D.h"
#include "HelloWorld\Engine\Time.h"
#include <list> 
#include <map>
using namespace std;

//player command that can be sent for networking
//It is for deterministic simulation so that each client can simulate the game only based on player inputs while keep sync
//the actual command time is the use tick and effecting time should be delayed to overcome the network latency




class PlayerCommand {
public:
	int useTick;
	int effectDelay;
	string name;

	b2Vec2 usePosition;
	b2Vec2 useDirection;
	int playerIndex;
};

class PlayerCommandExecuter {
public:
	//parse the command and use it
	virtual void ExecuteCommand(PlayerCommand command) = 0;
	virtual string GetCommandName() = 0;
};

///This is used to enqueue player command and execute them.
///This seems useless now,but it can be modified to support networking;
class PlayerCommandController {
public:
	PlayerCommandController(GameTime* time);
	~PlayerCommandController();

	void AddExecuter(PlayerCommandExecuter* executer);

	void EnqueueCommand(PlayerCommand command);

	void ExecuteCommands();
private:
	GameTime* time;
	list<PlayerCommand> commands;
	map<string, PlayerCommandExecuter*> executers;
};
#pragma once

#include "HelloWorld\Engine\GameObject.h"
#include "PlayerCommand.h"
#include "Abilities.h"


class Camera;

class GameController : public GameObject {
	
public:
	static GameController*  GetInstance();

	void AddPlayerPoint(bool isPlayerOne);
	int GetPlayerPoint(int index);

	void RegisterAbility(Ability* ability);
	void UseAbility(Ability* ability, b2Vec2 position, int playerIndex);

	///----------------callbacks-------------
	void Construct(SerializedGameObjectData* data) override;
	void OnGUI() override;
	void FixedUpdate(float32 deltaTime) override;
	void OnDestroyed() override;
	///-----------------------------------

	//just make those public to save my time...
	float playerOneMana = 3;
	float playerTwoMana = 3;
private:
	static GameController* instance;
	Camera * mainCamera;
	PlayerCommandController* commandController;

	int playerOnePoint = 0;
	int playerTwoPoint = 0;

	const float MAX_MANA = 10;
	const float MANA_REGEN_RATE = 0.7f;
};

inline GameController*  GameController::GetInstance() {
	return instance;
}
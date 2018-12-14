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

	void UseLargeBallAbility(b2Vec2);

	///----------------callbacks-------------
	void Construct(SerializedGameObjectData* data) override;
	void OnGUI() override;
	void FixedUpdate(float32 deltaTime) override;
	void OnDestroyed() override;
	///-----------------------------------
private:
	static GameController* instance;
	Camera * mainCamera;
	PlayerCommandController* commandController;

	
	///----------------a bunch of abilities-------------------
	AbilityLargeBall abilityLargeBall;
	///-----------------------------------------------------

	int playerOnePoint = 0;
	int playerTwoPoint = 0;



};

inline GameController*  GameController::GetInstance() {
	return instance;
}
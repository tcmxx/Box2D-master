#pragma once

#include "HelloWorld\Engine\GameObject.h"
class Camera;

class GameController : public GameObject {
	
public:
	static GameController*  GetInstance();

	void AddPlayerPoint(bool isPlayerOne);
	int GetPlayerPoint(int index);
	///----------------callbacks-------------
	void Construct(SerializedGameObjectData* data) override;
	void OnGUI() override;
	void FixedUpdate(float32 deltaTime) override;
	///-----------------------------------
private:
	static GameController* instance;
	Camera * mainCamera;

	int playerOnePoint = 0;
	int playerTwoPoint = 0;
};

inline GameController*  GameController::GetInstance() {
	return instance;
}
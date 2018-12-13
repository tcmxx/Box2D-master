#include "GameController.h"

#include "HelloWorld\Engine\Engine.h"
#include "TargetBall.h"

GameController* GameController::instance;




void GameController::AddPlayerPoint(bool isPlayerOne) {
	if (isPlayerOne) {
		playerOnePoint++;
	}
	else {
		playerTwoPoint++;
	}
}

int GameController::GetPlayerPoint(int index) {
	if (index == 0) {
		return playerOnePoint;
	}
	else {
		return playerTwoPoint;
	}
}


void GameController::Construct(SerializedGameObjectData* data) {
	instance = this;
	mainCamera = Engine::GetMainCamera();
}

void GameController::FixedUpdate(float32 deltaTime) {
	if (Engine::GetInput()->GetMouseDown(0)) {
		
		GetScene()->InstantiateGameObject<TargetBall>(mainCamera->ConvertScreenToWorld(Engine::GetInput()->GetMousePosition()), 0);
	}
}

void GameController::OnGUI() {
	return;

}
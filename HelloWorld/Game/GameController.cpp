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
	commandController = new PlayerCommandController(GetScene()->GetTime());
	commandController->AddExecuter(&abilityLargeBall);

}
void GameController::OnDestroyed() {
	delete commandController;
}
void GameController::FixedUpdate(float32 deltaTime) {
	if (Engine::GetInput()->GetMouseDown(0)) {
		//GetScene()->InstantiateGameObject<TargetBall>(mainCamera->ConvertScreenToWorld(Engine::GetInput()->GetMousePosition()), 0);
		UseLargeBallAbility(mainCamera->ConvertScreenToWorld(Engine::GetInput()->GetMousePosition()));
	}
	commandController->ExecuteCommands();
}

void GameController::OnGUI() {
	return;

}


void GameController::UseLargeBallAbility(b2Vec2 position) {
	commandController->EnqueueCommand(abilityLargeBall.GenerateCommand(position,0));
}
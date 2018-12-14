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
}
void GameController::OnDestroyed() {
	delete commandController;
}
void GameController::FixedUpdate(float32 deltaTime) {

	if (playerOneMana < MAX_MANA) {
		playerOneMana += deltaTime * MANA_REGEN_RATE;
	}
	if (playerTwoMana < MAX_MANA) {
		playerTwoMana += deltaTime * MANA_REGEN_RATE;
	}
	commandController->ExecuteCommands();
}

void GameController::OnGUI() {
	return;

}
void GameController::RegisterAbility(Ability* ability) {
	commandController->AddExecuter(ability);
}

void GameController::UseAbility(Ability* ability, b2Vec2 position, int playerIndex) {
	commandController->EnqueueCommand(ability->GenerateCommand(position, playerIndex));
}
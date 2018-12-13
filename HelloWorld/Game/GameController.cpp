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
	int menuWidth = 200;
	ImGui::SetNextWindowPos(ImVec2((float)mainCamera->m_width - menuWidth - 10, 10));
	ImGui::SetNextWindowSize(ImVec2((float)menuWidth, (float)mainCamera->m_height - 20));
	ImGui::Begin("Test UI", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
	ImGui::PushAllowKeyboardFocus(false); // Disable TAB

	ImGui::PushItemWidth(-1.0f);

	ImGui::Separator();

	int temp;
	float tempFLoat;
	bool tempBool;

	ImGui::Text("Vel Iters");
	ImGui::SliderInt("##Vel Iters", &temp, 0, 50);
	ImGui::Text("Pos Iters");
	ImGui::SliderFloat("##Hertz", &tempFLoat, 5.0f, 120.0f, "%.0f hz");
	ImGui::PopItemWidth();

	ImGui::Checkbox("Sleep", &tempBool);

	ImGui::Separator();

	ImGui::Checkbox("Shapes", &tempBool);

	ImVec2 button_sz = ImVec2(-1, 0);

	if (ImGui::Button("Quit", button_sz))
		Engine::Close();
	if (ImGui::Button("Test", button_sz)) {
		GetScene()->InstantiateGameObject<TargetBall>(b2Vec2(0, 20), 0);
	}
		

	ImGui::PopAllowKeyboardFocus();
	ImGui::End();

}
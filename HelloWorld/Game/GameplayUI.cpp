#include "GameplayUI.h"
#include "GameController.h"
#include <string> 

void GameplayUI::Construct(SerializedGameObjectData* data) {
	mainCamera = Engine::GetMainCamera();
}




void GameplayUI::OnGUI() {
	CreateAbilityButtons();
	CreateGameInfoUIs();
}

void GameplayUI::CreateGameInfoUIs() {


	int menuWidth = (SCORE_TEXT_SIZE.x + 10) * 3;

	ImGui::SetNextWindowPos(ImVec2(mainCamera->m_width / 2 - menuWidth / 2, 10));
	ImGui::SetNextWindowSize(ImVec2((float)menuWidth, SCORE_TEXT_SIZE.y + 20));
	ImGui::Begin("Overlay", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);
	ImGui::PushAllowKeyboardFocus(false); // Disable TAB

	ImGui::PushItemWidth(-1.0f);

	//ImGui::SetCursorPos(b2Vec2(float(mainCamera->m_width / 2 - menuWidth / 2)+20, float((SCORE_TEXT_SIZE.y + 20)/2+10)));
	ImGui::Text(("Player 1:" + std::to_string(GameController::GetInstance()->GetPlayerPoint(0))).c_str());
	ImGui::SameLine(menuWidth- SCORE_TEXT_SIZE.x);
	ImGui::Text(("Player 2:" + std::to_string(GameController::GetInstance()->GetPlayerPoint(1))).c_str());

	ImGui::PopAllowKeyboardFocus();
	ImGui::End();
}

void GameplayUI::CreateAbilityButtons() {

	// ability uis
	int menuWidth = (CARD_BUTTON_SIZE.x + 10) * 5;

	ImGui::SetNextWindowPos(ImVec2(10, 10));
	ImGui::SetNextWindowSize(ImVec2((float)menuWidth, CARD_BUTTON_SIZE.y + 20));
	ImGui::Begin("AbilityBar1", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);
	ImGui::PushAllowKeyboardFocus(false); // Disable TAB

	ImGui::PushItemWidth(-1.0f);

	if (ImGui::Button("Ability1", CARD_BUTTON_SIZE))
		Engine::Close();
	ImGui::SameLine();
	if (ImGui::Button("Ability2", CARD_BUTTON_SIZE))
		Engine::Close();
	ImGui::SameLine();
	if (ImGui::Button("Ability3", CARD_BUTTON_SIZE))
		Engine::Close();
	ImGui::SameLine();
	if (ImGui::Button("Ability4", CARD_BUTTON_SIZE))
		Engine::Close();
	ImGui::SameLine();
	if (ImGui::Button("Ability5", CARD_BUTTON_SIZE))
		Engine::Close();

	ImGui::PopAllowKeyboardFocus();
	ImGui::End();



	ImGui::SetNextWindowPos(ImVec2(mainCamera->m_width - 10 - menuWidth, 10));
	ImGui::SetNextWindowSize(ImVec2((float)menuWidth, CARD_BUTTON_SIZE.y + 20));
	ImGui::Begin("AbilityBar2", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);
	ImGui::PushAllowKeyboardFocus(false); // Disable TAB

	ImGui::PushItemWidth(-1.0f);

	if (ImGui::Button("Ability1", CARD_BUTTON_SIZE))
		Engine::Close();
	ImGui::SameLine();
	if (ImGui::Button("Ability2", CARD_BUTTON_SIZE))
		Engine::Close();
	ImGui::SameLine();
	if (ImGui::Button("Ability3", CARD_BUTTON_SIZE))
		Engine::Close();
	ImGui::SameLine();
	if (ImGui::Button("Ability4", CARD_BUTTON_SIZE))
		Engine::Close();
	ImGui::SameLine();
	if (ImGui::Button("Ability5", CARD_BUTTON_SIZE))
		Engine::Close();

	ImGui::PopAllowKeyboardFocus();
	ImGui::End();
}
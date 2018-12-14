#include "GameplayUI.h"
#include "GameController.h"
#include <string> 

bool AbilityButton::isInUse1 = false;
bool AbilityButton::isInUse2 = false;
b2Vec2 GameplayUI::playerTwoCursor;

AbilityButton::AbilityButton(Ability* ability, ImVec2 size, int playerIndex) :
	mAbility(ability), mSize(size), mPlayerIndex(playerIndex) {
	mName = ability->GetAbilityName();
	GameController::GetInstance()->RegisterAbility(ability);
}

void AbilityButton::Render() {

	string showText = mName.c_str();
	if (isPreparing) {
		showText = "Click To USE";
	}
	if (!ManaEnough()) {
		showText = "More Mana";
	}
	if (cooldownTimer > 0) {
		showText = std::to_string(cooldownTimer *Engine::GetScene()->GetTime()->GetTickInterval());
	}
	//showText = std::to_string(cooldownTimer);

	if (ImGui::Button(showText.c_str(), mSize)) {
		OnClicked();
	}

	if (isPreparing) {
		//render the range
		auto size = range.GetExtents();
		auto center = range.GetCenter();
		b2Color color = mPlayerIndex == 0 ? b2Color(0, 0.5, 0, 1) : b2Color(0, 0, 0.5, 1);
		Engine::GetDebugDraw()->DrawSolidBox(size, center, color);
	}
}
void AbilityButton::FixedUpdate() {
	if (cooldownTimer > 0)
		cooldownTimer--;
	if (isPreparing) {
		if (mPlayerIndex == 0) {
			if (Engine::GetInput()->GetMouseUp(0)) {
				auto position = Engine::GetMainCamera()->ConvertScreenToWorld(Engine::GetInput()->GetMousePosition());
				if (range.lowerBound.x < position.x && range.lowerBound.y < position.y
					&&range.upperBound.x > position.x && range.upperBound.y > position.y) {
					Use(position);
				}
			}
		}
		else {
			if (Engine::GetInput()->GetKeyDown(Space)) {
				auto position = GameplayUI::playerTwoCursor;
				if (range.lowerBound.x < position.x && range.lowerBound.y < position.y
					&&range.upperBound.x > position.x && range.upperBound.y > position.y) {
					Use(position);
				}
			}
		}
	}
}
void AbilityButton::OnClicked() {

	bool inUse = (mPlayerIndex == 0 ? isInUse1 : isInUse2);
	if (cooldownTimer <= 0 && !isPreparing && !inUse) {
		isPreparing = true;
		range = mAbility->GetRange(mPlayerIndex);
		if (mPlayerIndex == 0) {
			isInUse1 = true;
		}
		else {
			isInUse2 = true;
		}
	}
	else if (cooldownTimer <= 0 && isPreparing) {
		isPreparing = false;
		if (mPlayerIndex == 0) {
			isInUse1 = false;
		}
		else {
			isInUse2 = false;
		}
	}

}
void AbilityButton::Use(const ImVec2& position) {
	cooldownTimer = mAbility->GetCoolDownTick();
	isPreparing = false;
	GameController::GetInstance()->UseAbility(mAbility, position, mPlayerIndex);
	if (mPlayerIndex == 0) {
		isInUse1 = false;
		GameController::GetInstance()->playerOneMana -= mAbility->GetManaCost();
	}
	else {
		isInUse2 = false;
		GameController::GetInstance()->playerTwoMana -= mAbility->GetManaCost();
	}
}

bool AbilityButton::ManaEnough() {
	if (mPlayerIndex == 0) {
		return mAbility->GetManaCost() <= GameController::GetInstance()->playerOneMana;
	}
	else {
		return mAbility->GetManaCost() <= GameController::GetInstance()->playerTwoMana;
	}
}



void GameplayUI::Construct(SerializedGameObjectData* data) {
	mainCamera = Engine::GetMainCamera();
	button11 = new AbilityButton(&abilityLargeBall, CARD_BUTTON_SIZE, 0);
	button12 = new AbilityButton(&abiliityFloatingBeam, CARD_BUTTON_SIZE, 0);
	button13 = new AbilityButton(&abilitySmallCube, CARD_BUTTON_SIZE, 0);
	button14 = new AbilityButton(&abilityExplosion, CARD_BUTTON_SIZE, 0);
	//button15 = new AbilityButton(&abilityLargeBall, CARD_BUTTON_SIZE,  0);

	button21 = new AbilityButton(&abilityLargeBall, CARD_BUTTON_SIZE, 1);
	button22 = new AbilityButton(&abiliityFloatingBeam, CARD_BUTTON_SIZE,  1);
	button23 = new AbilityButton(&abilitySmallCube, CARD_BUTTON_SIZE, 1);
	button24 = new AbilityButton(&abilityExplosion, CARD_BUTTON_SIZE,  1);
	//button25 = new AbilityButton(&abilityLargeBall, CARD_BUTTON_SIZE,  1);

	GameController* gameController = GameController::GetInstance();
	gameController->RegisterAbility(&abilityLargeBall);
	gameController->RegisterAbility(&abiliityFloatingBeam);
	gameController->RegisterAbility(&abilitySmallCube);
	gameController->RegisterAbility(&abilityExplosion);
}


void GameplayUI::FixedUpdate(float32 deltaTime) {
	button11->FixedUpdate(); button12->FixedUpdate(); button13->FixedUpdate();
	button14->FixedUpdate(); 
	button21->FixedUpdate();
	button22->FixedUpdate(); button23->FixedUpdate(); button24->FixedUpdate();
	
	PlayerTwoControls();
}

void GameplayUI::PlayerTwoControls() {
	if (Engine::GetInput()->GetKeyDown(Num_1)) {
		button21->OnClicked();
	}
	else if (Engine::GetInput()->GetKeyDown(Num_2)) {
		button22->OnClicked();
	}else if (Engine::GetInput()->GetKeyDown(Num_3)) {
		button23->OnClicked();
	}else if (Engine::GetInput()->GetKeyDown(Num_4)) {
		button24->OnClicked();
	}

	if (Engine::GetInput()->GetKeyPressed(Arrow_Up)) {
		playerTwoCursor += PLAYER2_CURSOR_MOVE_SPEED*b2Vec2(0,1);
	}
	if (Engine::GetInput()->GetKeyPressed(Arrow_Down)) {
		playerTwoCursor += PLAYER2_CURSOR_MOVE_SPEED * b2Vec2( 0, -1);
	}
	if (Engine::GetInput()->GetKeyPressed(Arrow_Right)) {
		playerTwoCursor += PLAYER2_CURSOR_MOVE_SPEED * b2Vec2(1,0);
	}
	if (Engine::GetInput()->GetKeyPressed(Arrow_Left)) {
		playerTwoCursor += PLAYER2_CURSOR_MOVE_SPEED * b2Vec2(-1,0);
	}

}


void GameplayUI::OnGUI() {
	CreateAbilityButtons();
	CreateGameInfoUIs();
}
void GameplayUI::OnRender() {
	auto center = playerTwoCursor;
	float length = 0.2f;
	Engine::GetDebugDraw()->DrawSegment(center + b2Vec2(0, length), center - b2Vec2(0, length),
		b2Color(0, 0, 1, 1));
	Engine::GetDebugDraw()->DrawSegment(center + b2Vec2(length,0), center - b2Vec2(length, 0),
		b2Color(0, 0, 1, 1));
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
	ImGui::SameLine(menuWidth - SCORE_TEXT_SIZE.x);
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

	button11->Render();
	ImGui::SameLine();
	button12->Render();
	ImGui::SameLine();
	button13->Render();
	ImGui::SameLine();
	button14->Render();
	ImGui::SameLine();
	ImGui::Text(("Mana:" + std::to_string(GameController::GetInstance()->playerOneMana)).c_str());


	ImGui::PopAllowKeyboardFocus();
	ImGui::End();



	ImGui::SetNextWindowPos(ImVec2(mainCamera->m_width - 10 - menuWidth, 10));
	ImGui::SetNextWindowSize(ImVec2((float)menuWidth, CARD_BUTTON_SIZE.y + 20));
	ImGui::Begin("AbilityBar2", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);
	ImGui::PushAllowKeyboardFocus(false); // Disable TAB

	ImGui::PushItemWidth(-1.0f);

	button21->Render();
	ImGui::SameLine();
	button22->Render();
	ImGui::SameLine();
	button23->Render();
	ImGui::SameLine();
	button24->Render();
	ImGui::SameLine();
	ImGui::Text(("Mana:" + std::to_string(GameController::GetInstance()->playerTwoMana)).c_str());
	

	ImGui::PopAllowKeyboardFocus();
	ImGui::End();
}

void GameplayUI::OnDestroyed() {
	delete button11, button12, button13, button14;
	delete button21, button22, button23, button24;
}
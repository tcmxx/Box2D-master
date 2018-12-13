#pragma once

#include "HelloWorld\Engine\GameObject.h"
#include "HelloWorld\Engine\Engine.h"


class GameplayUI : public GameObject {

public:
	///----------------callbacks-------------
	void Construct(SerializedGameObjectData* data) override;
	void OnGUI() override;
	//void FixedUpdate(float32 deltaTime) override;
	///-----------------------------------
private:
	void CreateAbilityButtons();
	void CreateGameInfoUIs();

	const ImVec2 CARD_BUTTON_SIZE = ImVec2(80, 120);
	const ImVec2 SCORE_TEXT_SIZE = ImVec2(80, 60);

	Camera * mainCamera;
};

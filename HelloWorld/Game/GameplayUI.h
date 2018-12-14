#pragma once

#include "HelloWorld\Engine\GameObject.h"
#include "HelloWorld\Engine\Engine.h"
#include "Abilities.h"

using namespace std;

class AbilityButton {
public:
	AbilityButton(Ability* ability, ImVec2 size, int playerIndex);
	void Render();
	void FixedUpdate();
	void OnClicked();
	void Use(const ImVec2& position);
private:
	bool ManaEnough();

	static bool isInUse1;
	static bool isInUse2;

	bool isPreparing = false;
	int cooldownTimer = 0;

	ImVec2 mSize;
	Ability* mAbility;
	string mName;
	int mPlayerIndex;

	b2AABB range;
};

class GameplayUI : public GameObject {

public:
	///----------------callbacks-------------
	void Construct(SerializedGameObjectData* data) override;
	void OnRender() override;
	void OnGUI() override;
	void OnDestroyed() override;
	void FixedUpdate(float32 deltaTime) override;
	///-----------------------------------

	static b2Vec2 playerTwoCursor; 
private:
	void CreateAbilityButtons();
	void CreateGameInfoUIs();

	void PlayerTwoControls();

	const ImVec2 CARD_BUTTON_SIZE = ImVec2(80, 120);
	const ImVec2 SCORE_TEXT_SIZE = ImVec2(80, 60);
	const float32 PLAYER2_CURSOR_MOVE_SPEED = 0.3f;

	Camera * mainCamera;

	///----------------a bunch of abilities-------------------
	AbilityLargeBall abilityLargeBall;
	AbilityFloatingBeam abiliityFloatingBeam;
	AbilitySmallCube abilitySmallCube;
	AbilityExplosion abilityExplosion;
	///-----------------------------------------------------
	AbilityButton *button11, *button12, *button13, *button14;
	AbilityButton *button21, *button22, *button23, *button24;
};


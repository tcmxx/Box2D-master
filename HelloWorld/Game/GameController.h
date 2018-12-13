#pragma once

#include "HelloWorld\Engine\GameObject.h"
class Camera;

class GameController : public GameObject {

public:
	void OnInstantiated()  override;
	void OnGUI() override;
	void FixedUpdate(float32 deltaTime) override;
private:
	Camera * mainCamera;
};
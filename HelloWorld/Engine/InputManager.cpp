#include "InputManager.h"
#include "HelloWorld\glfw\glfw3.h"

InputManager::InputManager() {}
InputManager::~InputManager() {}

bool InputManager::GetKeyDown(KeyCode key) {
	std::map<KeyCode, bool>::iterator it = down.find(key);
	if (it != down.end()) {
		return down[key];
	}
	else {
		return false;
	}
}
bool InputManager::GetKeyPressed(KeyCode key) {
	std::map<KeyCode, bool>::iterator it = pressed.find(key);
	if (it != pressed.end()) {
		return pressed[key];
	}
	else {
		return false;
	}
}

bool InputManager::GetMouseDown(int button) {
	std::map<int, bool>::iterator it = mouseDown.find(button);
	if (it != mouseDown.end()) {
		return mouseDown[button];
	}
	else {
		return false;
	}
}
bool InputManager::GetMouseUp(int button) {
	std::map<int, bool>::iterator it = mouseUp.find(button);
	if (it != mouseUp.end()) {
		return mouseUp[button];
	}
	else {
		return false;
	}
}

b2Vec2 InputManager::GetMouseDelta() {
	return b2Vec2(deltaX, deltaY);
}


void InputManager::Flush() {
	down.clear();
	up.clear();
	mouseDown.clear();
	mouseUp.clear();
	deltaX = 0;
	deltaY = 0;
}


void InputManager::MouseDeltaCallBack(float xd, float yd) {
	deltaX = xd;
	deltaY = yd;
}

void InputManager::MouseCallBack(int button, int action, int mods) {
	if (action == GLFW_PRESS)
	{
		mouseDown[button] = true;
	}
	else if (action == GLFW_RELEASE)
	{
		mouseUp[button] = true;
	}
}

void InputManager::KeyCallBack(int key, int scancode, int action, int mods) {
	
	if (action == GLFW_PRESS)
	{
		switch (key)
		{
		case GLFW_KEY_LEFT:
			down[Arrow_Left] = true;
			pressed[Arrow_Left] = true;
			break;
		case GLFW_KEY_RIGHT:
			down[Arrow_Right] = true;
			pressed[Arrow_Right] = true;
			break;

		case GLFW_KEY_DOWN:
			down[Arrow_Down] = true;
			pressed[Arrow_Down] = true;
			break;

		case GLFW_KEY_UP:
			down[Arrow_Up] = true;
			pressed[Arrow_Up] = true;
			break;
		case GLFW_KEY_SPACE:
			down[Space] = true;
			pressed[Space] = true;
			break;

		case GLFW_KEY_1:
			down[Num_1] = true;
			pressed[Num_1] = true;
			break;

		case GLFW_KEY_2:
			down[Num_2] = true;
			pressed[Num_2] = true;
			break;

		case GLFW_KEY_3:
			down[Num_3] = true;
			pressed[Num_3] = true;
			break;

		case GLFW_KEY_4:
			down[Num_4] = true;
			pressed[Num_4] = true;
			break;

		}
	}
	else if (action == GLFW_RELEASE)
	{
		switch (key)
		{
		case GLFW_KEY_LEFT:
			up[Arrow_Left] = true;
			pressed[Arrow_Left] = false;
			break;
		case GLFW_KEY_RIGHT:
			up[Arrow_Right] = true;
			pressed[Arrow_Right] = false;
			break;

		case GLFW_KEY_DOWN:
			up[Arrow_Down] = true;
			pressed[Arrow_Down] = false;
			break;

		case GLFW_KEY_UP:
			up[Arrow_Up] = true;
			pressed[Arrow_Up] = false;
			break;
		case GLFW_KEY_SPACE:
			up[Space] = true;
			pressed[Space] = false;
			break;

		case GLFW_KEY_1:
			up[Num_1] = true;
			pressed[Num_1] = false;
			break;

		case GLFW_KEY_2:
			up[Num_2] = true;
			pressed[Num_2] = false;
			break;

		case GLFW_KEY_3:
			up[Num_3] = true;
			pressed[Num_3] = false;
			break;

		case GLFW_KEY_4:
			up[Num_4] = true;
			pressed[Num_4] = false;
			break;

		}
	}
}




#pragma once

#include <map>

#include "Box2D\Box2D.h"

//for now only have those keys that might be used by me
enum KeyCode {
	Space,
	Arrow_Up,
	Arrow_Down,
	Arrow_Right,
	Arrow_Left,
	Num_1,
	Num_2,
	Num_3,
	Num_4
};



class InputManager {

public:
	InputManager();
	~InputManager();

	bool GetKeyDown(KeyCode key);
	bool GetKeyPressed(KeyCode key);

	bool GetMouseDown(int button);
	bool GetMouseUp(int button);

	b2Vec2 GetMouseDelta();

protected:
	friend class Engine;

	void KeyCallBack(int key, int scancode, int action, int mods);
	void MouseCallBack(int key, int action, int mods);
	void MouseDeltaCallBack(float xd, float yd);

	void Flush();
private:

	std::map<KeyCode, bool> down;
	std::map<KeyCode, bool> up;
	std::map<KeyCode, bool> pressed;

	std::map<int, bool> mouseDown;
	std::map<int, bool> mouseUp;
	//std::map<int, bool> mousePressed;

	float deltaX = 0;
	float deltaY = 0;
};


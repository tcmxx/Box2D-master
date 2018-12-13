#pragma once


#include "GameObject.h"
#include "Component.h"
#include "Scene.h"
#include "Rigidbody2D.h"
#include "CircleCollider2D.h"
#include "BoxCollider2D.h"
#include "Camera.h"
#include "InputManager.h"

#include "HelloWorld\DebugDraw.h"

#if defined(__APPLE__)
#define GLFW_INCLUDE_GLCOREARB
#include <OpenGL/gl3.h>
#else
#include "HelloWorld\glad\glad.h"
#endif
#include "HelloWorld\glfw\glfw3.h"
#include "HelloWorld\imgui\imgui.h"
#include "HelloWorld\imgui\imgui_impl_glfw_gl3.h"
#include <stdio.h>

#ifdef _MSC_VER
#define snprintf _snprintf
#endif

// This include was added to support MinGW
#ifdef _WIN32
#include <crtdbg.h>
#endif





//class GLFWwindow;
//class DebugDraw;
/// The simple engine is designed only for my Frogmind's coding test. 
/// It uses basic component based architecture, only support 2D and optimization & extensibility are not considered that much...
/// It also uses a lot of codes/utilities from the Box2D TestBed codes.
class Engine {

public:
	Engine();
	~Engine();

	static int Initialize();
	static void Run();
	static void Close();

	static Scene* GetScene();
	static Camera* GetMainCamera();
	static DebugDraw* GetDebugDraw();
	static InputManager* GetInput();
	static Physics2D* GetPhysics2D();
protected:
	static void glfwErrorCallback(int error, const char *description);
	static void sScrollCallback(GLFWwindow* window, double dx, double dy);
	static void sResizeWindow(GLFWwindow*, int width, int height);
	static void sKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void sCharCallback(GLFWwindow* window, unsigned int c);
	static void sMouseButton(GLFWwindow* window, int32 button, int32 action, int32 mods);
	static void sMouseMotion(GLFWwindow*, double xd, double yd);

	static void sCreateUI(GLFWwindow* window);
private:
	static GLFWwindow * mainWindow;
	static Camera mainCamera;
	static Scene scene;	//right now only one scene is supported
	static DebugDraw debugDraw;
	static InputManager input;
};


inline Scene* Engine::GetScene() {
	return &scene;
}
inline Camera* Engine::GetMainCamera() {
	return &mainCamera;
}
inline DebugDraw* Engine::GetDebugDraw() {
	return &debugDraw;
}

inline InputManager* Engine::GetInput() {
	return &input;
}

inline Physics2D* Engine::GetPhysics2D() {
	return &scene.physics2D;
}





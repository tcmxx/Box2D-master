#include "Engine.h"


GLFWwindow* Engine::mainWindow = nullptr;
Camera Engine::mainCamera;
Scene Engine::scene = Scene(60);
DebugDraw Engine::debugDraw;

Engine::Engine()
{
}


Engine::~Engine()
{
}




int Engine::Initialize() {

#if defined(_WIN32)
	// Enable memory-leak reports
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG));
#endif
	glfwSetErrorCallback(glfwErrorCallback);

	//g_camera.m_width = 1024;
	//g_camera.m_height = 640;

	if (glfwInit() == 0)
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return -1;
	}

	char title[64];
	sprintf(title, "Game");

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	mainWindow = glfwCreateWindow(mainCamera.m_width, mainCamera.m_height, title, NULL, NULL);
	//
	if (mainWindow == NULL)
	{
		fprintf(stderr, "Failed to open GLFW mainWindow.\n");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(mainWindow);

#if defined(__APPLE__) == FALSE
	// Load OpenGL functions using glad
	if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) == 0)
	{
		printf("Failed to initialize OpenGL context\n");
		return -1;
	}
#endif



	printf("OpenGL %s, GLSL %s\n", glGetString(GL_VERSION), glGetString(GL_SHADING_LANGUAGE_VERSION));

	glfwSetWindowSizeCallback(mainWindow, sResizeWindow);
	glfwSetKeyCallback(mainWindow, sKeyCallback);
	glfwSetCharCallback(mainWindow, sCharCallback);
	glfwSetMouseButtonCallback(mainWindow, sMouseButton);
	glfwSetCursorPosCallback(mainWindow, sMouseMotion);
	glfwSetScrollCallback(mainWindow, sScrollCallback);



	sCreateUI(mainWindow);
	glfwSwapInterval(1);

	glClearColor(0.3f, 0.3f, 0.3f, 1.f);//TODO:replace with clear color of camera

	//debug draw
	debugDraw.Create(&mainCamera);
}

Scene* Engine::GetScene() {
	return &scene;
}
Camera* Engine::GetMainCamera() {
	return &mainCamera;
}
DebugDraw* Engine::GetDebugDraw() {
	return &debugDraw;
}
void Engine::Run() {
	// This is our little game loop.
	while (!glfwWindowShouldClose(mainWindow))
	{
		glfwGetWindowSize(mainWindow, &mainCamera.m_width, &mainCamera.m_height);

		int bufferWidth, bufferHeight;
		glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);
		glViewport(0, 0, bufferWidth, bufferHeight);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		ImGui_ImplGlfwGL3_NewFrame();
		ImGui::SetNextWindowPos(ImVec2(0, 0));
		ImGui::SetNextWindowSize(ImVec2((float)mainCamera.m_width, (float)mainCamera.m_height));
		ImGui::Begin("Overlay", NULL, ImVec2(0, 0), 0.0f, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoScrollbar);
		ImGui::SetCursorPos(ImVec2(5, (float)mainCamera.m_height - 20));
		ImGui::End();




		scene.FixedUpdate();
		// Now print the position and angle of the body.
		//auto trans = comp->GetTransform();
		//b2Vec2 position = trans.p;
		//float32 angle = trans.q.GetAngle();

		//printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);

		debugDraw.Flush();

		sInterface();

		ImGui::Render();
		glfwSwapBuffers(mainWindow);
		glfwPollEvents();
	}


	debugDraw.Destroy();
}



//
void Engine::sInterface()
{
	int menuWidth = 200;
	ImGui::SetNextWindowPos(ImVec2((float)mainCamera.m_width - menuWidth - 10, 10));
	ImGui::SetNextWindowSize(ImVec2((float)menuWidth, (float)mainCamera.m_height - 20));
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
		glfwSetWindowShouldClose(mainWindow, GL_TRUE);

	ImGui::PopAllowKeyboardFocus();
	ImGui::End();


}


void Engine::glfwErrorCallback(int error, const char *description)
{
	fprintf(stderr, "GLFW error occured. Code: %d. Description: %s\n", error, description);
}
//
void Engine::sCreateUI(GLFWwindow* window)
{
	// Init UI
	const char* fontPath = "Data/DroidSans.ttf";
	ImGui::GetIO().Fonts->AddFontFromFileTTF(fontPath, 15.f);

	if (ImGui_ImplGlfwGL3_Init(window, false) == false)
	{
		fprintf(stderr, "Could not init GUI renderer.\n");
		assert(false);
		return;
	}

	ImGuiStyle& style = ImGui::GetStyle();
	style.FrameRounding = style.GrabRounding = style.ScrollbarRounding = 2.0f;
	style.FramePadding = ImVec2(4, 2);
	style.DisplayWindowPadding = ImVec2(0, 0);
	style.DisplaySafeAreaPadding = ImVec2(0, 0);
}



//
void Engine::sScrollCallback(GLFWwindow* window, double dx, double dy)
{
	ImGui_ImplGlfwGL3_ScrollCallback(window, dx, dy);
	bool mouse_for_ui = ImGui::GetIO().WantCaptureMouse;

	if (!mouse_for_ui)
	{
		if (dy > 0)
		{
			//g_camera.m_zoom /= 1.1f;
		}
		else
		{
			//g_camera.m_zoom *= 1.1f;
		}
	}
}
//
void Engine::sResizeWindow(GLFWwindow* window, int width, int height)
{
	//g_camera.m_width = width;
	//g_camera.m_height = height;
}

//
void Engine::sKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	ImGui_ImplGlfwGL3_KeyCallback(window, key, scancode, action, mods);
	bool keys_for_ui = ImGui::GetIO().WantCaptureKeyboard;
	if (keys_for_ui)
		return;

	if (action == GLFW_PRESS)
	{
		switch (key)
		{
		case GLFW_KEY_ESCAPE:
			// Quit
			glfwSetWindowShouldClose(mainWindow, GL_TRUE);
			break;

		case GLFW_KEY_LEFT:
			// Pan left
			if (mods == GLFW_MOD_CONTROL)
			{
			}
			else
			{
				//g_camera.m_center.x -= 0.5f;
			}
			break;

		case GLFW_KEY_RIGHT:
			// Pan right
			if (mods == GLFW_MOD_CONTROL)
			{
			}
			else
			{
				//g_camera.m_center.x += 0.5f;
			}
			break;

		case GLFW_KEY_DOWN:
			// Pan down
			if (mods == GLFW_MOD_CONTROL)
			{
			}
			else
			{
				//g_camera.m_center.y -= 0.5f;
			}
			break;

		case GLFW_KEY_UP:
			// Pan up
			if (mods == GLFW_MOD_CONTROL)
			{
			}
			else
			{
				//g_camera.m_center.y += 0.5f;
			}
			break;

		case GLFW_KEY_HOME:
			// Reset view
			//g_camera.m_zoom = 1.0f;
			//g_camera.m_center.Set(0.0f, 20.0f);
			break;

		case GLFW_KEY_Z:
			// Zoom out
			//g_camera.m_zoom = b2Min(1.1f * g_camera.m_zoom, 20.0f);
			break;

		case GLFW_KEY_X:
			// Zoom in
			//g_camera.m_zoom = b2Max(0.9f * g_camera.m_zoom, 0.02f);
			break;

		case GLFW_KEY_R:
			break;

		case GLFW_KEY_SPACE:
			break;

		case GLFW_KEY_O:
			break;

		case GLFW_KEY_P:
			break;

		case GLFW_KEY_LEFT_BRACKET:
			break;

		case GLFW_KEY_RIGHT_BRACKET:
			break;

		}
	}
	else if (action == GLFW_RELEASE)
	{
	}
	// else GLFW_REPEAT
}

//
void Engine::sCharCallback(GLFWwindow* window, unsigned int c)
{
	ImGui_ImplGlfwGL3_CharCallback(window, c);
}

//
void Engine::sMouseButton(GLFWwindow* window, int32 button, int32 action, int32 mods)
{
	ImGui_ImplGlfwGL3_MouseButtonCallback(window, button, action, mods);

	double xd, yd;
	glfwGetCursorPos(mainWindow, &xd, &yd);
	b2Vec2 ps((float32)xd, (float32)yd);

	// Use the mouse to move things around.
	if (button == GLFW_MOUSE_BUTTON_1)
	{
		//<##>
		//ps.Set(0, 0);
		//b2Vec2 pw = g_camera.ConvertScreenToWorld(ps);
		if (action == GLFW_PRESS)
		{
			if (mods == GLFW_MOD_SHIFT)
			{
			}
			else
			{
			}
		}

		if (action == GLFW_RELEASE)
		{
		}
	}
	else if (button == GLFW_MOUSE_BUTTON_2)
	{
		if (action == GLFW_PRESS)
		{
		}

		if (action == GLFW_RELEASE)
		{
		}
	}
}

//
 void Engine::sMouseMotion(GLFWwindow*, double xd, double yd)
{
	b2Vec2 ps((float)xd, (float)yd);

	//b2Vec2 pw = g_camera.ConvertScreenToWorld(ps);
}
#include "Engine.h"





GLFWwindow* Engine::mainWindow = nullptr;
Camera Engine::mainCamera;
Scene Engine::scene = Scene(60);
DebugDraw Engine::debugDraw;
InputManager Engine::input;

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


		debugDraw.Flush();
		input.Flush();

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
void Engine::sResizeWindow(GLFWwindow* window, int width, int height)
{
	mainCamera.m_width = width;
	mainCamera.m_height = height;
}
void Engine::sCharCallback(GLFWwindow* window, unsigned int c)
{
	ImGui_ImplGlfwGL3_CharCallback(window, c);
}


//----------------- Input callbacks----------------------
//-----------------------------------------------------------


void Engine::sKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	ImGui_ImplGlfwGL3_KeyCallback(window, key, scancode, action, mods);
	bool keys_for_ui = ImGui::GetIO().WantCaptureKeyboard;
	if (keys_for_ui)
		return;

	input.KeyCallBack(key, scancode, action, mods);
}

//
void Engine::sMouseButton(GLFWwindow* window, int32 button, int32 action, int32 mods)
{
	ImGui_ImplGlfwGL3_MouseButtonCallback(window, button, action, mods);

	double xd, yd;
	glfwGetCursorPos(mainWindow, &xd, &yd);
	b2Vec2 ps((float32)xd, (float32)yd);

	input.MouseCallBack(button, action, mods);
}

//
 void Engine::sMouseMotion(GLFWwindow*, double xd, double yd)
{
	 input.MouseDeltaCallBack((float)xd, (float)yd);
}

 //
 void Engine::sScrollCallback(GLFWwindow* window, double dx, double dy)
 {
	 ImGui_ImplGlfwGL3_ScrollCallback(window, dx, dy);
	 bool mouse_for_ui = ImGui::GetIO().WantCaptureMouse;
 }
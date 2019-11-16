#include "Editor.h"
#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
#include <GL/gl3w.h>    // Initialize with gl3wInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
#include <GL/glew.h>    // Initialize with glewInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
#include <glad/glad.h>  // Initialize with gladLoadGL()
//#else
//#include IMGUI_IMPL_OPENGL_LOADER_CUSTOM
#endif

#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include <stdio.h>
#include "Debug.h"
#include "Render.h"

bool show_save_window = false;
bool show_new_window = false;
bool show_creationWindow = false;
ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

MouseMode currentMouseMode;
void EditorStartup(GLFWwindow* window) 
{
#if __APPLE__
	// GL 3.2 + GLSL 150
	const char* glsl_version = "#version 150";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else
	// GL 3.0 + GLSL 130
	const char* glsl_version = "#version 130";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif


	currentMouseMode = MenuMode;


#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
	bool err = gl3wInit() != 0;
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
	bool err = glewInit() != GLEW_OK;
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
	bool err = gladLoadGL() == 0;
#else
	bool err = false; // If you use IMGUI_IMPL_OPENGL_LOADER_CUSTOM, your loader is likely to requires some form of initialization.
#endif

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);
}



void ShowMenuBar() 
{
	ImGui::BeginMainMenuBar();


	if (ImGui::BeginMenu("New")) 
	{
		if (ImGui::MenuItem("New 3D Model")) 
		{
		}
		if (ImGui::MenuItem("New 2D Model")) 
		{
			ImGui::OpenPopup("CreationWindow");
			show_creationWindow = true;
		}
		ImGui::EndMenu();
	}
	if (ImGui::BeginMenu("Open"))
	{
		
	}
	if (ImGui::BeginMenu("Save", "CTRL+S"))
	{
		if (ImGui::MenuItem("Save")) 
		{
		}
		if (ImGui::MenuItem("Save As"))
		{
		}
	}

	if (ImGui::BeginMenu("Options"))
	{
		static bool enabled = true;
		ImGui::MenuItem("Enabled", "", &enabled);
		ImGui::BeginChild("child", ImVec2(0, 60), true);
		for (int i = 0; i < 10; i++)
			ImGui::Text("Scrolling Text %d", i);
		ImGui::EndChild();
		static float f = 0.5f;
		static int n = 0;
		static bool b = true;
		ImGui::SliderFloat("Value", &f, 0.0f, 1.0f);
		ImGui::InputFloat("Input", &f, 0.1f);
		ImGui::Combo("Combo", &n, "Yes\0No\0Maybe\0\0");
		ImGui::Checkbox("Check", &b);
		ImGui::EndMenu();
	}

	ImGui::EndMainMenuBar();
}

void EditorUpdate(GLFWwindow* window)
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	ShowMenuBar();

	//if (show_demo_window)
	//	ImGui::ShowDemoWindow(&show_demo_window);

	//{
	//	static float f = 0.0f;
	//	static int counter = 0;
	//	ImGui::Begin("MAADeditor");                         // Create a window called "Hello, world!" and append into it.

	//	ImGui::ColorEdit3("clear color", (float*)& clear_color); // Edit 3 floats representing a color

	//	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	//	ImGui::End();
	//}

	ImGui::SetNextWindowPos(ImVec2(1, 1), ImGuiCond_FirstUseEver);
	if (show_creationWindow) 
	{
		ImGui::Begin("Creation Window");
		ImGui::Text("Test");

		ImGui::End();
	}



	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

}

void EditorShutdown() 
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

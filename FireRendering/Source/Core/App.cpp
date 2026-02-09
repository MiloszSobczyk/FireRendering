#include "App.h"

#include "Core/Globals.h"

Camera App::camera = Camera(5.f, 45.f);

App::App() : 
	window(Globals::StartingWidth, Globals::StartingHeight, "Don't lose your way"),
	scene(std::make_shared<FireScene>())
{
	InitImgui(window.GetWindowPointer());

	HandleResize();
}

App::~App()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();
}

void App::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	scene->RenderOnScene();
}

void App::RenderUI()
{
	ImGuiWindowFlags windowFlags =
		ImGuiWindowFlags_NoTitleBar
		| ImGuiWindowFlags_NoMove
		| ImGuiWindowFlags_NoResize
		| ImGuiWindowFlags_NoCollapse;
}

void App::HandleInput()
{
	if (ImGui::IsAnyItemActive() || ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow))
	{
		return;
	}

	camera.HandleInput();
}

void App::Run()
{
	while (!window.ShouldClose())
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		scene->Update();

		RenderUI();

		Render();

		HandleInput();

		ImGui::Render();

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		window.ProcessFrame();
	}
}

void App::HandleResize()
{
	float newWidth = static_cast<float>(window.GetWidth());
	float newHeight = static_cast<float>(window.GetHeight());
	float aspect = newWidth / newHeight;

	camera.SetAspect(aspect);
}
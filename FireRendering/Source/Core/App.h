#pragma once

#include "Core/Window.h"
#include "Engine/Camera.h"
#include "Managers/ShaderManager.h"
#include "Objects/Objects.h"
#include "Utils/Init.h"

#include <array>
#include <string>
#include <unordered_set>
#include <vector>

#include "Scenes/FireScene.h"

class App 
{
private:
	Window window;

	static Camera camera;

	std::shared_ptr<FireScene> scene;

	void Render();
	void RenderUI();
	void HandleInput();

public:
	App();
	~App();

	void Run();
	void HandleResize();

	inline static glm::mat4x4 GetProjectionMatrix() { return camera.GetProjectionMatrix(); }
	inline static glm::mat4x4 GetViewMatrix() { return camera.GetViewMatrix(); }
	inline static glm::vec3 GetCameraWorldPosition() { return camera.GetWorldPosition(); }
};
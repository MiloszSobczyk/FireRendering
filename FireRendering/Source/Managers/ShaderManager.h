#pragma once

#include "Engine/Shader.h"
#include "Engine/ShaderBuilder.h"
#include <string>
#include <unordered_map>

enum class ShaderName
{
	Default = 0,
	DefaultColor = 1,
	DefaultPhong = 2,
	BezierPatch = 3,
	Billboard = 4,
	Fire = 5
};

class ShaderManager
{
private:
	std::unordered_map<ShaderName, std::shared_ptr<Shader>> shaders;

	ShaderManager();
public:
	ShaderManager(ShaderManager& shaderManager) = delete;
	void operator=(const ShaderManager& shaderManager) = delete;
	
	static ShaderManager& GetInstance();

	void AddShader(ShaderName name, std::shared_ptr<Shader> shader);
	std::shared_ptr<Shader> GetShader(ShaderName name);
};

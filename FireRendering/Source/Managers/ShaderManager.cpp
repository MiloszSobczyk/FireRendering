#include "ShaderManager.h"
#include <iostream>

ShaderManager::ShaderManager()
{
	AddShader(
		ShaderName::Default,
		ShaderBuilder()
		.SetShaderDirectory("Resources/Shaders/")
		.AddShader(ShaderType::Vertex, "default")
		.AddShader(ShaderType::Fragment, "default")
		.Compile()
	);

	AddShader(
		ShaderName::DefaultColor,
		ShaderBuilder()
		.SetShaderDirectory("Resources/Shaders/")
		.AddShader(ShaderType::Vertex, "defaultColor")
		.AddShader(ShaderType::Fragment, "defaultColor")
		.Compile()
	);

	AddShader(
		ShaderName::DefaultPhong,
		ShaderBuilder()
		.SetShaderDirectory("Resources/Shaders/")
		.AddShader(ShaderType::Vertex, "defaultPhong")
		.AddShader(ShaderType::Fragment, "defaultPhong")
		.Compile()
	);

	AddShader(
		ShaderName::BezierPatch,
		ShaderBuilder()
		.SetShaderDirectory("Resources/Shaders/")
		.AddShader(ShaderType::Vertex, "bezierPatch")
		.AddShader(ShaderType::TessControl, "bezierPatch")
		.AddShader(ShaderType::TessEvaluation, "bezierPatch")
		.AddShader(ShaderType::Fragment, "bezierPatch")
		.Compile()
	);
}

ShaderManager& ShaderManager::GetInstance()
{
	static ShaderManager instance;

	return instance;
}

void ShaderManager::AddShader(ShaderName name, std::shared_ptr<Shader> shader)
{
	if (shaders.find(name) != shaders.end())
	{
		std::cerr << "Shader already exists: " << static_cast<int>(name) << '\n';
		return;
	}

	shaders[name] = shader;
}

std::shared_ptr<Shader> ShaderManager::GetShader(ShaderName name)
{
	return shaders[name];
}

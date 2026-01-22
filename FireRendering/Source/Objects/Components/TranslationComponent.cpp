#include "TranslationComponent.h"

#include <imgui/imgui.h>
#include <glm/gtc/matrix_transform.hpp>

TranslationComponent::TranslationComponent()
	: translation(0.f, 0.f, 0.f, 0.f)
{
}

TranslationComponent::TranslationComponent(const glm::vec4& translation)
	: translation(translation)
{
}

glm::vec4 TranslationComponent::GetTranslation() const
{
	return translation;
}

void TranslationComponent::SetTranslation(const glm::vec4& translation)
{
	this->translation = translation;
}

void TranslationComponent::AddTranslation(const glm::vec4& translation)
{
	this->translation += translation;
}

glm::mat4x4 TranslationComponent::GetMatrix() const
{
	glm::mat4x4 matrix(1.0f);
	matrix = glm::translate(matrix, glm::vec3(translation.x, translation.y, translation.z));
	return matrix;
}

void TranslationComponent::RenderUI()
{
	ImGui::InputFloat3("Translation", &translation.x, "%.3f");
}
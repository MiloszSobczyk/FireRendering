#pragma once

#include "Shape.h"
#include "Engine/Renderer.h"

class Arrow : public Shape, public ITranslation, public IScaling, public IRotation
{
private:
	std::shared_ptr<TranslationComponent> translationComponent;
	std::shared_ptr<ScalingComponent> scalingComponent;
	std::shared_ptr<RotationComponent> rotationComponent;
	Renderer<PositionVertexData> renderer;

	glm::vec3 point1;
	glm::vec3 point2;

	void UpdateTransform();

public:
	Arrow();
	~Arrow() = default;

	void Render() override;

	void SetPoint1(const glm::vec3& point1);
	void SetPoint2(const glm::vec3& point2);

	std::shared_ptr<TranslationComponent> GetTranslationComponent() override;
	std::shared_ptr<ScalingComponent> GetScalingComponent() override;
	std::shared_ptr<RotationComponent> GetRotationComponent() override;
	glm::mat4x4 GetModelMatrix() override;
};
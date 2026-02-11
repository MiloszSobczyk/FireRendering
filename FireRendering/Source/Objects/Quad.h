#pragma once

#include "Shape.h"
#include "Engine/Renderer.h"

class Quad : public Shape, public ITranslation, public IScaling, public IRotation
{
private:
	std::shared_ptr<TranslationComponent> translationComponent;
	std::shared_ptr<ScalingComponent> scalingComponent;
	std::shared_ptr<RotationComponent> rotationComponent;
	Renderer<PositionUVData> renderer;

public:
	Quad();
	~Quad() = default;

	void Render() override;

	void Update();

	std::shared_ptr<TranslationComponent> GetTranslationComponent() override;
	std::shared_ptr<ScalingComponent> GetScalingComponent() override;
	std::shared_ptr<RotationComponent> GetRotationComponent() override;
	glm::mat4x4 GetModelMatrix() override;
};
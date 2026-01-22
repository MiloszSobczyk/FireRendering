#pragma once

#include "Shape.h"
#include "Engine/Renderer.h"

class Plane : public Shape, public ITranslation, public IScaling
{
private:
	std::shared_ptr<TranslationComponent> translationComponent;
	std::shared_ptr<ScalingComponent> scalingComponent;
	Renderer<PositionVertexData> renderer;

public:
	Plane();
	~Plane() = default;

	void Render() override;

	void Update();

	std::shared_ptr<TranslationComponent> GetTranslationComponent() override;
	std::shared_ptr<ScalingComponent> GetScalingComponent() override;
	glm::mat4x4 GetModelMatrix() override;
};
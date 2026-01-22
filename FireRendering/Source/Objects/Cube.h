#pragma once

#include "Shape.h"
#include "Engine/Renderer.h"

class Cube : public Shape, public ITranslation, public IScaling, public IRotation
{
private:
	bool needsUpdate = true;
	bool inverted;
	bool edgesOnly;
	bool usePhong;

	std::shared_ptr<TranslationComponent> translationComponent;
	std::shared_ptr<ScalingComponent> scalingComponent;
	std::shared_ptr<RotationComponent> rotationComponent;
	Renderer<PositionNormalVertexData> renderer;

public:
	Cube(bool inInverted = false, bool inEdgesOnly = false, bool inUsePhong = true);
	~Cube() = default;

	void Render() override;

	void Update();

	std::shared_ptr<TranslationComponent> GetTranslationComponent() override;
	std::shared_ptr<ScalingComponent> GetScalingComponent() override;
	std::shared_ptr<RotationComponent> GetRotationComponent() override;
	glm::mat4x4 GetModelMatrix() override;
};
#pragma once

#include "Shape.h"
#include "Engine/Renderer.h"
#include "Objects/Components/TranslationComponent.h"

class Spring : public Shape
{
private:
	bool needsUpdate = true;

	Renderer<PositionVertexData> renderer;

	int coils = 5;
	int segmentsPerCoil = 40;
	int ringSegments = 16;

	float R = 3.f;
	float r = .5f;
	float pitch = 0.f;

	float topPoint;
	float bottomPoint;

public:
	Spring(float inTopPoint, float inBottomPoint);
	~Spring() = default;

	void Render() override;

	void Update();

	void SetTopPoint(float inTopPoint);
	void SetBottomPoint(float inBottomPoint);
};
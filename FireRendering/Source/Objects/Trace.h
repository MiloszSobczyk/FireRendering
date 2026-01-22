#pragma once

#include "Shape.h"
#include "Engine/Renderer.h"

#include <deque>

class Trace : public Shape
{
private:
	bool needsUpdate = true;
	Renderer<PositionVertexData> renderer;
	std::deque<PositionVertexData> points;

	int traceSize = 100;

public:
	Trace();
	~Trace() = default;

	void Render() override;

	void Update();

	void SetTraceSize(int inTraceSize);
	void AddPoint(const glm::vec3& point);
	void ClearPoints();
};
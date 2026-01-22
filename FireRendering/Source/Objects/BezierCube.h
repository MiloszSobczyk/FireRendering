#pragma once

#include "Engine/Renderer.h"
#include "Shape.h"
#include "Cube.h"

#include <array>
#include <glm/glm.hpp>
#include <unordered_map>
#include <vector>

class BezierCube : public Shape
{
private:
	bool drawCube = true;
	bool drawControlFrame = true;
	bool drawShortSprings = false;
	bool drawLongSprings = false;
	bool drawPoints = false;

	bool useControlFrame = true;
	int selectedPoint = 0;

	Renderer<PositionVertexData> cubeRenderer;
	Renderer<PositionVertexData> controlFrameRenderer;
	Renderer<PositionVertexData> shortSpringsRenderer;
	Renderer<PositionVertexData> longSpringsRenderer;

	float edgeLength;

	std::array<std::shared_ptr<Cube>, 64> points;

	std::array<glm::vec3, 64> cubePoints;
	std::array<glm::vec3, 8> framePoints;
	// Frame spring -> Cube spring
	std::unordered_map<int, int> frameSprings;
	// i -> j -> spring rest length, where j < i
	std::unordered_map<int, std::unordered_map<int, float>> springsRestLengths;

	std::array<glm::vec3, 8> originalFramePoints;
	glm::vec3 localFrameOffset;
	glm::vec3 rotationAngles;
	glm::vec3 lastOffset;
	glm::vec3 lastRotation;

private:
	void ResetCube();
	void ResetFrame();

	void UpdateCubeRenderer();
	void UpdateControlFrameRenderer();
	void UpdateShortSpringsRenderer();
	void UpdateLongSpringsRenderer();

	std::vector<unsigned int> GetBezierPatchesIndices();
	std::vector<unsigned int> GetShortSpringsIndices();
	std::vector<unsigned int> GetLongSpringsIndices();

	void RenderControlFrameUI();
	void RenderPointsUI();

	void ApplyPointHighlighting();

public:
	BezierCube(float inEdgeLength = 1.f);
	~BezierCube() = default;

	void Render() override;
	void RenderUI() override;

	void Reset(float inEdgeLength = 1.f);

	void SetEdgeLength(float inEdgeLength);
	void SetCubePoints(std::array<glm::vec3, 64>);
	void SetFramePoints(std::array<glm::vec3, 8>);
	
	inline std::array<glm::vec3, 64> GetCubePoints() const { return cubePoints; };
	inline std::array<glm::vec3, 8> GetFramePoints() const { return framePoints; };
	inline const std::unordered_map<int, int>& GetFrameSprings() { return frameSprings; };
	inline const std::unordered_map<int, std::unordered_map<int, float>>& GetSpringsRestLengths() { return springsRestLengths; };

	inline const bool GetUseControlFrame() const { return useControlFrame; }
};
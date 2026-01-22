#pragma once

#include "Utils/Logger.h"
#include <glm/glm.hpp>

enum class VertexDataType
{
	PositionVertexData,
	PositionColorVertexData,
	PositionNormalVertexData,
};

struct PositionVertexData
{
	glm::vec4 Position;
};

struct PositionNormalVertexData
{
	glm::vec4 Position;
	glm::vec4 Normal;
};

struct PositionColorVertexData
{
	glm::vec4 Position;
	glm::vec4 Color;
};
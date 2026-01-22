#include "Shape.h"

#include <glm/gtc/matrix_transform.hpp>

Shape::Shape(glm::vec4 inColor)
	: color(inColor) , initialMatrix(glm::identity<glm::mat4x4>())
{
}

glm::mat4x4 Shape::GetModelMatrix()
{
    return glm::identity<glm::mat4x4>();
}
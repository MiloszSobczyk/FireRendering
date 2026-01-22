#include "Trace.h"

#include "Managers/ShaderManager.h"
#include "Core/App.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

Trace::Trace()
	: renderer(VertexDataType::PositionVertexData)
{
}

void Trace::Render()
{
	auto shader = ShaderManager::GetInstance().GetShader(ShaderName::Default);

	shader->Bind();
	shader->SetUniformVec4f("u_color", color);
	shader->SetUniformMat4f("u_viewMatrix", App::GetViewMatrix());
	shader->SetUniformMat4f("u_projectionMatrix", App::GetProjectionMatrix());
	shader->SetUniformMat4f("u_modelMatrix", GetModelMatrix());

	renderer.Render(GL_LINE_STRIP);
	shader->Unbind();
}

void Trace::Update()
{
	if (!needsUpdate)
		return;

	needsUpdate = false;

	while (points.size() > traceSize)
	{
		points.pop_back();
	}

	std::vector<PositionVertexData> vertices;

	for (int i = 0; i < points.size(); ++i)
	{
		vertices.push_back(points[i]);
	}

	renderer.SetVertices(vertices);
}

void Trace::SetTraceSize(int inTraceSize)
{
	traceSize = inTraceSize;
	needsUpdate = true;
}

void Trace::AddPoint(const glm::vec3& point)
{
	points.push_front({{ point.x, point.y, point.z, 1.f }});
	needsUpdate = true;
}

void Trace::ClearPoints()
{
	points.clear();
	needsUpdate = true;
}

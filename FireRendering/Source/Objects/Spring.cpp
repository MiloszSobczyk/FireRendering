#include "Spring.h"
#include "Core/App.h"

#include <numbers>
#include <glm/gtc/matrix_transform.hpp>

Spring::Spring(float inTopPoint, float inBottomPoint)
    : Shape(ColorPalette::Get(Color::White)), renderer(VertexDataType::PositionVertexData),
	topPoint(inTopPoint), bottomPoint(inBottomPoint)
{
    Update();
}

// It could just draw same segment multiple times but with different model matrix
void Spring::Render()
{
    auto shader = ShaderManager::GetInstance().GetShader(ShaderName::Default);

    shader->Bind();
    shader->SetUniformVec4f("u_color", color);
    shader->SetUniformMat4f("u_viewMatrix", App::GetViewMatrix());
    shader->SetUniformMat4f("u_projectionMatrix", App::GetProjectionMatrix());
    shader->SetUniformMat4f("u_modelMatrix", GetModelMatrix());

    renderer.Render(GL_TRIANGLES);

    shader->Unbind();
}

void Spring::Update()
{
    if (!needsUpdate)
		return;

	needsUpdate = false;

	pitch = (topPoint - bottomPoint) / coils;

    std::vector<PositionVertexData> vertices;
    std::vector<unsigned int> indices;

    for (int i = 0; i <= coils * segmentsPerCoil; ++i)
    {
        float theta = (2.0f * std::numbers::pi_v<float> * i) / segmentsPerCoil;

        // Helix center point
        float cx = R * cos(theta);
        float cy = bottomPoint + ((topPoint - bottomPoint) * theta) / (2.0f * std::numbers::pi_v<float> * coils);
        float cz = R * sin(theta);

        for (int j = 0; j <= ringSegments; ++j)
        {
            float phi = (2.0f * std::numbers::pi_v<float> * j) / ringSegments;

            // Local coordinates for the circular cross section
            float x = cx + r * cos(phi) * cos(theta);
            float y = cy + r * sin(phi);
            float z = cz - r * cos(phi) * sin(theta);

            vertices.push_back({ { x, y, z, 1.0f } });
        }
    }

    int verticesPerRing = ringSegments + 1;
    int totalRings = coils * segmentsPerCoil;

    for (int i = 0; i < totalRings; ++i)
    {
        for (int j = 0; j < ringSegments; ++j)
        {
            int i0 = i * verticesPerRing + j;
            int i1 = i0 + verticesPerRing;
            int i2 = i0 + 1;
            int i3 = i1 + 1;

            indices.push_back(i0);
            indices.push_back(i1);
            indices.push_back(i2);

            indices.push_back(i2);
            indices.push_back(i1);
            indices.push_back(i3);
        }
    }

    renderer.SetVertices(vertices);
    renderer.SetIndices(indices);
}

void Spring::SetTopPoint(float inTopPoint)
{
    if (topPoint != inTopPoint)
    {
	    topPoint = inTopPoint;
        needsUpdate = true;
    }
}

void Spring::SetBottomPoint(float inBottomPoint)
{
    if (bottomPoint != inBottomPoint)
    {
        bottomPoint = inBottomPoint;
        needsUpdate = true;
	}
}

#include "Cube.h"
#include "Core/App.h"

#include <glm/gtc/matrix_transform.hpp>

Cube::Cube(bool inInverted, bool inEdgesOnly, bool inUsePhong)
    : inverted(inInverted), edgesOnly(inEdgesOnly), usePhong(inUsePhong), Shape(ColorPalette::Get(Color::Purple)), 
    renderer(VertexDataType::PositionNormalVertexData), 
    translationComponent(std::make_shared<TranslationComponent>()),
    rotationComponent(std::make_shared<RotationComponent>()),
    scalingComponent(std::make_shared<ScalingComponent>())
{
    Update();
}

void Cube::Render()
{
    //if (edgesOnly)
    //{
    //    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //}

    //auto shader = ShaderManager::GetInstance().GetShader(usePhong ? ShaderName::DefaultPhong : ShaderName::Default);

    //shader->Bind();
    //shader->SetUniformVec4f("u_color", color);
    //shader->SetUniformMat4f("u_viewMatrix", App::GetViewMatrix());
    //shader->SetUniformMat4f("u_projectionMatrix", App::GetProjectionMatrix());
    //shader->SetUniformMat4f("u_modelMatrix", GetModelMatrix());

    renderer.Render(GL_TRIANGLES);

    //shader->Unbind();

    //if (edgesOnly)
    //{
    //    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    //}
}

void Cube::Update()
{
    if (!needsUpdate)
        return;

	needsUpdate = false;

    std::vector<PositionNormalVertexData> vertices;
    std::vector<unsigned int> indices;

    auto addFace = [&](glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec3 d, glm::vec3 normal)
        {
            if (inverted)
            {
                normal = -normal;
            }
            
            unsigned int startIndex = static_cast<unsigned int>(vertices.size());

            if (!inverted)
            {
                vertices.push_back({ { a.x, a.y, a.z, 1.f }, { normal.x, normal.y, normal.z, 0.f } });
                vertices.push_back({ { b.x, b.y, b.z, 1.f }, { normal.x, normal.y, normal.z, 0.f } });
                vertices.push_back({ { c.x, c.y, c.z, 1.f }, { normal.x, normal.y, normal.z, 0.f } });
                vertices.push_back({ { d.x, d.y, d.z, 1.f }, { normal.x, normal.y, normal.z, 0.f } });
            }
            else
            {
                vertices.push_back({ { d.x, d.y, d.z, 1.f }, { normal.x, normal.y, normal.z, 0.f } });
                vertices.push_back({ { c.x, c.y, c.z, 1.f }, { normal.x, normal.y, normal.z, 0.f } });
                vertices.push_back({ { b.x, b.y, b.z, 1.f }, { normal.x, normal.y, normal.z, 0.f } });
                vertices.push_back({ { a.x, a.y, a.z, 1.f }, { normal.x, normal.y, normal.z, 0.f } });
            }

            indices.push_back(startIndex + 0);
            indices.push_back(startIndex + 3);
            indices.push_back(startIndex + 2);

            indices.push_back(startIndex + 2);
            indices.push_back(startIndex + 1);
            indices.push_back(startIndex + 0);
        };


    glm::vec3 p0(-0.5f, -0.5f, -0.5f);
    glm::vec3 p1(0.5f, -0.5f, -0.5f);
    glm::vec3 p2(0.5f, 0.5f, -0.5f);
    glm::vec3 p3(-0.5f, 0.5f, -0.5f);
    glm::vec3 p4(-0.5f, -0.5f, 0.5f);
    glm::vec3 p5(0.5f, -0.5f, 0.5f);
    glm::vec3 p6(0.5f, 0.5f, 0.5f);
    glm::vec3 p7(-0.5f, 0.5f, 0.5f);

    addFace(p0, p1, p2, p3, glm::vec3(0.f, 0.f, -1.f)); // Front
    addFace(p5, p4, p7, p6, glm::vec3(0.f, 0.f, +1.f)); // Back
    addFace(p4, p0, p3, p7, glm::vec3(-1.f, 0.f, 0.f)); // Left
    addFace(p1, p5, p6, p2, glm::vec3(+1.f, 0.f, 0.f)); // Right
    addFace(p4, p5, p1, p0, glm::vec3(0.f, -1.f, 0.f)); // Bottom
    addFace(p3, p2, p6, p7, glm::vec3(0.f, +1.f, 0.f)); // Top

    renderer.SetVertices(vertices);
    renderer.SetIndices(indices);
}

std::shared_ptr<TranslationComponent> Cube::GetTranslationComponent()
{
    return translationComponent;
}

std::shared_ptr<ScalingComponent> Cube::GetScalingComponent()
{
    return scalingComponent;
}

std::shared_ptr<RotationComponent> Cube::GetRotationComponent()
{
    return rotationComponent;
}

glm::mat4x4 Cube::GetModelMatrix()
{
    return translationComponent->GetMatrix() 
        * rotationComponent->GetMatrix() 
        * scalingComponent->GetMatrix() 
        * initialMatrix;
}
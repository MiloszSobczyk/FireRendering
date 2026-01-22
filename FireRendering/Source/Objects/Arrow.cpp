#include "Arrow.h"

#include "Managers/ShaderManager.h"
#include "Core/App.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

void Arrow::UpdateTransform()
{
    glm::vec3 dir = point2 - point1;
    float length = glm::length(dir);

    if (length < 1e-6f)
    {
        scalingComponent->SetScaling(glm::vec3(0.0f));
        return;
    }

    glm::vec3 dirNorm = glm::normalize(dir);
    glm::vec3 defaultDir = glm::vec3(1.0f, 0.0f, 0.0f);

    float dot = glm::dot(defaultDir, dirNorm);
    if (dot > 1.0f) dot = 1.0f;
    if (dot < -1.0f) dot = -1.0f;

    float angle = glm::acos(dot);
    glm::vec3 axis = glm::cross(defaultDir, dirNorm);

    if (glm::length(axis) < 1e-6f)
    {
        axis = glm::vec3(0, 1, 0);
        angle = 0.0f;
    }
    else
    {
        axis = glm::normalize(axis);
    }

    rotationComponent->SetRotation(glm::angleAxis(angle, axis));
    translationComponent->SetTranslation(glm::vec4(point1, 1.0f));
    scalingComponent->SetScaling(glm::vec3(length, 1.0f, 1.0f));
}

Arrow::Arrow()
    : Shape(ColorPalette::Get(Color::Purple)),
    renderer(VertexDataType::PositionVertexData),
    translationComponent(std::make_shared<TranslationComponent>()),
    rotationComponent(std::make_shared<RotationComponent>()),
    scalingComponent(std::make_shared<ScalingComponent>()),
    point1(glm::vec3(0.f)), point2(glm::vec3(1.f, 0.f, 0.f))
{
    float shaftLength = 0.8f;
    float shaftHalf = 0.02f;
    float headLength = 0.2f;
    float headHalf = 0.1f;

    std::vector<PositionVertexData> vertices;

    glm::vec3 p0(0.f, shaftHalf, shaftHalf);
    glm::vec3 p1(0.f, shaftHalf, -shaftHalf);
    glm::vec3 p2(0.f, -shaftHalf, -shaftHalf);
    glm::vec3 p3(0.f, -shaftHalf, shaftHalf);

    glm::vec3 p4(shaftLength, shaftHalf, shaftHalf);
    glm::vec3 p5(shaftLength, shaftHalf, -shaftHalf);
    glm::vec3 p6(shaftLength, -shaftHalf, -shaftHalf);
    glm::vec3 p7(shaftLength, -shaftHalf, shaftHalf);

    auto addQuad = [&vertices](glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec3 d)
        {
            vertices.push_back({ { a.x, a.y, a.z, 1.f } });
            vertices.push_back({ { b.x, b.y, b.z, 1.f } });
            vertices.push_back({ { c.x, c.y, c.z, 1.f } });

            vertices.push_back({ { a.x, a.y, a.z, 1.f } });
            vertices.push_back({ { c.x, c.y, c.z, 1.f } });
            vertices.push_back({ { d.x, d.y, d.z, 1.f } });
        };

    addQuad(p0, p1, p2, p3);
    addQuad(p4, p5, p6, p7);
    addQuad(p0, p1, p5, p4);
    addQuad(p3, p2, p6, p7);
    addQuad(p1, p2, p6, p5);
    addQuad(p0, p3, p7, p4);

    glm::vec3 tip(shaftLength + headLength, 0.f, 0.f);
    glm::vec3 b1(shaftLength, headHalf, headHalf);
    glm::vec3 b2(shaftLength, headHalf, -headHalf);
    glm::vec3 b3(shaftLength, -headHalf, -headHalf);
    glm::vec3 b4(shaftLength, -headHalf, headHalf);

    auto addTri = [&vertices](glm::vec3 a, glm::vec3 b, glm::vec3 c)
        {
            vertices.push_back({ { a.x, a.y, a.z, 1.f } });
            vertices.push_back({ { b.x, b.y, b.z, 1.f } });
            vertices.push_back({ { c.x, c.y, c.z, 1.f } });
        };

    addTri(tip, b1, b2);
    addTri(tip, b2, b3);
    addTri(tip, b3, b4);
    addTri(tip, b4, b1);

    addQuad(b1, b2, b3, b4);

    renderer.SetVertices(vertices);
}


void Arrow::Render()
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

void Arrow::SetPoint1(const glm::vec3& p1)
{
    point1 = p1;
    UpdateTransform();
}

void Arrow::SetPoint2(const glm::vec3& p2)
{
    point2 = p2;
    UpdateTransform();
}

std::shared_ptr<TranslationComponent> Arrow::GetTranslationComponent()
{
    return translationComponent;
}

std::shared_ptr<ScalingComponent> Arrow::GetScalingComponent()
{
    return scalingComponent;
}

std::shared_ptr<RotationComponent> Arrow::GetRotationComponent()
{
    return rotationComponent;
}

glm::mat4x4 Arrow::GetModelMatrix()
{
    return translationComponent->GetMatrix()
        * rotationComponent->GetMatrix()
        * scalingComponent->GetMatrix();
}

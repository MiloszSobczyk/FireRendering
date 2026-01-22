#pragma once

#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

class TranslationComponent
{
private:
    glm::vec4 translation;

public:
    TranslationComponent();
    TranslationComponent(const glm::vec4& translation);

    glm::vec4 GetTranslation() const;
    virtual void SetTranslation(const glm::vec4& translation);
    virtual void AddTranslation(const glm::vec4& translation);
    glm::mat4x4 GetMatrix() const;

    void RenderUI();
};
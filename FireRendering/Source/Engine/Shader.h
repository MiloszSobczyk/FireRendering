#pragma once

#include <glm/glm.hpp>

#include <string>
#include <unordered_map>

class Shader 
{
public:
    Shader(unsigned int programID);
    ~Shader();

    void Bind() const;
    void Unbind() const;

    void SetUniformMat4f(const std::string& name, const glm::mat4x4& matrix);
    void SetUniformVec4f(const std::string& name, const glm::vec4& vector);
    void SetUniformVec3f(const std::string& name, const glm::vec3& vector);
	void SetUniformInt(const std::string& name, int value);
    void SetUniformFloat(const std::string& name, float value);

private:
    unsigned int m_RendererID;
    mutable std::unordered_map<std::string, int> m_UniformLocationCache;

    int GetUniformLocation(const std::string& name);
};

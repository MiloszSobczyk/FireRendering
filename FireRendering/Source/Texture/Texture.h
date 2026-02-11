#pragma once

#include <string>
#include <GL/glew.h> 

class Texture
{
public:
    Texture() = default;

    bool LoadFromFile(const std::string& path, bool flipVertically = true);

    void Bind(unsigned int unit = 0) const;

    void Release();

    inline GLuint GetID() const { return ID; }
    inline int GetWidth() const { return width; }
    inline int GetHeight() const { return height; }

private:
    GLuint ID = 0;
    int width = 0;
    int height = 0;
    int channels = 0;
};
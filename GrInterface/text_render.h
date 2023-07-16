#pragma once
#define GLFW_INCLUDE_NONE
#include "./glad/glad.h"
#include <GLFW/glfw3.h>
#include <string>

class Texture
{
public:
    Texture(GLenum TextureTarget, const std::string& FileName);
 
    bool Load();
 
    void Bind(GLenum TextureUnit);
};
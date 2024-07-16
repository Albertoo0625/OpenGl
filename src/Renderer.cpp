// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include<iostream>
#include"Renderer.h"
#include"VertexArray.h"
#include "IndexBuffer.h"
#include "shader.h"

void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
};

bool GLCheckError(const char* function, const char* file, int line)
{
    while (GLenum error = glGetError()) {
        /*std::cout << "[glError] " << error <<function << file<< line << std::endl;*/
        std::cout << "[glError] " << error << function << file << line << std::endl;
        return false;
    };
    return true;
};

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
    shader.Bind();
    va.Bind();
    ib.Bind();
    glcall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::Clear() 
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

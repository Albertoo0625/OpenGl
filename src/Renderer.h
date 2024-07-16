#pragma once

#include<GL/glew.h>
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "shader.h"

#define ASSERT(x) if(!(x)) __debugbreak();

#define glcall(x) GLClearError();\
      x;\
ASSERT (GLCheckError(#x,__FILE__,__LINE__));


void GLClearError();


bool GLCheckError(const char* function, const char* file, int line);

class Renderer
{
public:
    void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
    void Clear();
};


 

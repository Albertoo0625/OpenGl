#include"IndexBuffer.h"
#include"Renderer.h"


IndexBuffer::IndexBuffer(const unsigned int* data,unsigned int count)
    :m_Count(count)
{
    /*glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);*/
    ASSERT(sizeof(unsigned int) == sizeof(GLuint));
    glGenBuffers(1, &m_Renderer_id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Renderer_id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
    glDeleteBuffers(1, &m_Renderer_id);
  
}

void IndexBuffer::Bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Renderer_id);
}

void IndexBuffer::Unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}



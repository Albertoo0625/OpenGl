#include"VertexArray.h"
#include<iostream>
#include<string>
#include"VertexBufferLayout.h"

VertexArray::VertexArray()
	:m_Renderer_id(0)
{
	glGenVertexArrays(1, &m_Renderer_id);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1,&m_Renderer_id);
}

void VertexArray::Bind() const
{
	glBindVertexArray(m_Renderer_id);
}

void VertexArray::UnBind() const
{
	glBindVertexArray(0);
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{ 
	Bind();
	vb.Bind();
	const auto& elements = layout.GetElements();
	unsigned int offset = 0;
	for (unsigned int i = 0;i < elements.size();i++)
	{
		const auto& element = elements[i];
		glVertexAttribPointer(i, element.count,element.type, element.normalized, layout.GetStride(),(const void*)offset);
		offset += element.count * sizeof(element.type);
		glEnableVertexAttribArray(i);
	}

}

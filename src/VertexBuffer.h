#pragma once

class VertexBuffer 
{
private:
	unsigned int m_Renderer_id;
public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;

};

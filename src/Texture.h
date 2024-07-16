#pragma once
#include"Renderer.h"

class Texture
{
private:
	unsigned int m_Renderer_id;
	std::string m_filepath;
	unsigned char* m_localbuffer;
	int m_Height, m_Width, m_BPP;
public:
	Texture(const std::string& path);
	~Texture();

	void Bind(unsigned int slot = 0) const;
	void UnBind() const;

	inline int GetWidth() const { return m_Width; };
	inline int GetHeight() const { return m_Height; };
};
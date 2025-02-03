#pragma once
#include<string>
#include<unordered_map>
#include"glm/glm.hpp"

struct ShaderStrings {
	std::string vertexshader;
	std::string fragmentshader;
};

class Shader
{
private:
	unsigned int m_Renderer_id;
	std::unordered_map<std::string,int>m_LocationCache;
	std::string m_Filepath;
	

public:

	Shader(const std::string& filepath);
	~Shader();

	void Bind() const;
	void UnBind() const;

	void setUniform1i(const std::string& name,int value);
	void setUniform4f(const std::string& name,float v1,float v2,float v3,float v4);
	void setUniformMat4(const std::string& name,const glm::mat4& matrix);
	ShaderStrings ParseShader(const std::string& filepath);
	int GetUniformLocation(const std::string& name);



private:
	
	unsigned int CompileShader(unsigned int type, const std::string& source);
	unsigned int CreateShader(const std::string& vertexshader, const std::string& fragmentshader);
};
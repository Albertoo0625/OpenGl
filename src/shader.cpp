// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com


#include"shader.h"
#include"Renderer.h"
#include<iostream>
#include<string>
#include<fstream>
#include<sstream>



Shader::Shader(const std::string& filepath)
    :m_Filepath(filepath),m_Renderer_id(0),m_LocationCache(0)
{
    ShaderStrings source = ParseShader(filepath);
    m_Renderer_id = CreateShader(source.vertexshader, source.fragmentshader);

}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source) {
    const int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, NULL);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
    
        char* message = (char*)_malloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << "shader" << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;

    }

    return id;
}



unsigned int Shader::CreateShader(const std::string& vertexshader, const std::string& fragmentshader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexshader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentshader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    return 1;

}

Shader::~Shader()
{
    glDeleteProgram(m_Renderer_id);
}

void Shader::Bind() const
{
    glUseProgram(m_Renderer_id);
}

void Shader::UnBind() const
{
    glUseProgram(0);
}


void Shader::setUniform1i(const std::string& name, int value)
{
    glUniform1i(GetUniformLocation(name), value);
}

void Shader::setUniform4f(const std::string& name, float v1, float v2, float v3, float v4)
{ 
    glUniform4f(GetUniformLocation(name), v1, v2, v3, v4);
}

void Shader::setUniformMat4(const std::string& name, const glm::mat4& matrix)
{
    glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
}

ShaderStrings Shader::ParseShader(const std::string& filepath)
{

    std::ifstream stream(filepath);

    enum class shaderType
    {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    shaderType type = shaderType::NONE;

    while (getline(stream, line))
    {
        if (line.find("#shader") != (std::string::npos))
        {
            if (line.find("vertex") != (std::string::npos))
            {
                type = shaderType::VERTEX;
            }
            else if (line.find("fragment") != (std::string::npos))
            {
                type = shaderType::FRAGMENT;
            }
        }
        else {

            glcall(ss[(int)type] << line << '\n');
        }
    }

    return { ss[0].str(),ss[1].str() };
}


int Shader::GetUniformLocation(const std::string& name)
{
    if (m_LocationCache.find(name) != m_LocationCache.end())
        return m_LocationCache[name];
    int location=glGetUniformLocation(m_Renderer_id, name.c_str());
    if (location== -1) {
        /*std::cout << "uniform does not exist" << std::endl;*/
    }
    return location;
}





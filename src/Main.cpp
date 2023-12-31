// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include"GL/glew.h"
#include <glfw3.h>
#include<iostream>
#include<string>
#include<fstream>
#include<sstream>

#define ASSERT(x) if(!(x)) __debugbreak();

#define glcall(x) GLClearError();\
      x;\
ASSERT (GLCheckError(#x,__FILE__,__LINE__));





static void GLClearError() {
    while (glGetError() != GL_NO_ERROR);
};

static bool GLCheckError(const char* function,const char* file,int line) {
    while (GLenum error = glGetError()) {
        /*std::cout << "[glError] " << error <<function << file<< line << std::endl;*/
        std::cout << "[glError] " << error <<function << file<< line << std::endl;
        return false;
    };
    return true;
};
const unsigned int CompileShader(unsigned int type, const std::string& source) {
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

struct ShaderStrings
{
    std::string vertexsource;
    std::string fragmentsource;
};

const ShaderStrings parseShader(const std::string& filepath)
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
            
            ss[(int)type] << line << '\n';
        }
    }

    return { ss[0].str(),ss[1].str() };

}

static unsigned int CreateShader(const std::string& vertexshader, const std::string& fragmentshader)
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



int main(void)
{
    
    GLFWwindow* window;

    

    /* Initialize the library */
    if (!glfwInit())
    {
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (glewInit() == GLEW_OK) {
        std::cout << "glew setup done" << std::endl;
    }

    float positions[] = {
        -0.5f,-0.5f,
         0.5f,-0.5f,
         0.5f,0.5f,
        -0.5f,0.5f
    };

    unsigned int indices[] = {
        0,1,2,
        2,3,0
    };

    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 4 * 2 * sizeof(float), positions, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
    glEnableVertexAttribArray(0);


    unsigned int ibo;
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);
   

    std::string filepath = "res/shaders/Basic.shader";
    ShaderStrings source = parseShader(filepath);
    std::cout << source.vertexsource << std::endl;

    unsigned int shader = CreateShader(source.vertexsource, source.fragmentsource);
    glUseProgram(shader);

    int location = glGetUniformLocation(shader, "u_Color");
    ASSERT(location != -1);
    float r = 0.0f;
    float l = 0.0f;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        
        float increment = 0.05f;
        if (r > 1.0f) {
            increment = -0.05f;
            r += increment;
            l += increment;
        }
        else if (r < 1.0f)
        {
            increment = +0.05f;
            r += increment;
            l += increment;
        }
        glUniform4f(location, r, 0.0f,l, 1.0f);
        glcall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    //glDeleteProgram(program);
    glfwTerminate();
    return 0;
}
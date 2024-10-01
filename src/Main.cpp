// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include"GL/glew.h"
#include<glfw3.h>
#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include"Renderer.h"
#include"VertexBuffer.h"
#include"IndexBuffer.h"
#include"VertexArray.h"
#include"shader.h"
#include"Texture.h"
#include"Vendor/glm/glm.hpp"
#include"Vendor/glm/gtc/matrix_transform.hpp"
#include"Vendor/glm/gtc/type_ptr.hpp"
#include"Vendor/Imgui/imgui.h"
#include"Vendor/Imgui/imgui_impl_opengl3.h"
#include"Vendor/Imgui/imgui_impl_glfw.h"



int main(void)
{
    GLFWwindow* window;
    unsigned int width = 720;
    unsigned int height = 1280;

    /* Initialize the library */
    if (!glfwInit())
    {
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(height, width, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    

    ImGui::CreateContext(); 
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();
    ImGui::StyleColorsDark();

    if (glewInit() == GLEW_OK) {
        std::cout << "glew setup done" << std::endl;
    }

    //float positions[] = {
    //    -0.5f,-0.5f,0.0f,0.0,
    //     0.5f,-0.5f,1.0f,0.0f,
    //     0.5f,0.5f,1.0f,1.0f,
    //    -0.5f,0.5f,0.0f,1.0f
    //};

    float positions[] =
    { //     COORDINATES     /   TexCoord  //
        -0.5f, 0.0f,  0.5f,    	0.0f, 0.0f,
        -0.5f, 0.0f, -0.5f,    	1.0f, 0.0f,
         0.5f, 0.0f, -0.5f,    	0.0f, 0.0f,
         0.5f, 0.0f,  0.5f,    	1.0f, 0.0f,
         0.0f, 0.8f,  0.0f,    	0.5f, 1.0f
    };




    //unsigned int indices[] = {
    //    0,1,2,
    //    2,3,0
    //};

    unsigned int indices[] =
    {
        0, 1, 2,
        0, 2, 3,
        0, 1, 4,
        1, 2, 4,
        2, 3, 4,
        3, 0, 4
    };

    //unsigned int vao;
    //glGenVertexArrays(1, &vao);
    //glBindVertexArray(vao);

    VertexArray va;
    VertexBuffer vb(positions, sizeof(positions)); // VertexBuffer vb(positions, 4 * 4 * sizeof(float));
    VertexBufferLayout layout;
    layout.push<float>(3);
    layout.push<float>(2);
    va.AddBuffer(vb, layout);
 

   


    //unsigned int buffer;
    //glGenBuffers(1, &buffer);
    //glBindBuffer(GL_ARRAY_BUFFER, buffer);
    //glBufferData(GL_ARRAY_BUFFER, 4 * 2 * sizeof(float), positions, GL_STATIC_DRAW);

    //glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
    //glEnableVertexAttribArray(0);

  /*  glm::mat4 proj=glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.5, 0, 0));
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));*/

    // Variables that help the rotation of the pyramid
    float rotation = 0.0f;
    double prevTime = glfwGetTime();

    // Enables the Depth Buffer
    glEnable(GL_DEPTH_TEST);


   



    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    IndexBuffer ib(indices, 18);

    //unsigned int ibo;
    //glGenBuffers(1, &ibo);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);
   
    Texture texture("res/Textures/brick.png");
 
  
    Shader shader("res/shaders/Basic.shader");

    Renderer renderer;
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        renderer.Clear();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        

        
        shader.Bind();
        texture.Bind();
        shader.setUniform1i("u_Texture", 0);
        
        shader.setUniform4f("u_Color", 0.8f, 0.5f, 0.3f, 1.0f);

        // Simple timer
        double crntTime = glfwGetTime();
        if (crntTime - prevTime >= 1 / 60)
        {
            rotation += 0.05f;
            prevTime = crntTime;
        }

        // Initializes matrices so they are not the null matrix
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 proj = glm::mat4(1.0f);


        ImGui::Begin("My Gui");

        ImGui::Text("hello world");
        // Generate samples and plot them
        float samples[100];
        for (int n = 0; n < 100; n++)
            samples[n] = sinf(n * 0.2f + (float)ImGui::GetTime() * 1.5f);
        ImGui::PlotLines("Samples", samples, 100);

        glm::vec3 translation(0.0f, 1.0f, 0.0f);
        glm::vec3 v_camPos(0.0f, -0.5f, -2.0f);

        ImGui::SliderFloat3("float", &translation.x, 0.0f, 1.0f);
        ImGui::SliderFloat3("Camera position", &v_camPos.x, -100.0f, -1.0f);

        ImGui::End();

        ImGui::Render();

        

        model = glm::rotate(model, glm::radians(rotation), translation);
        view = glm::translate(view,v_camPos);
        proj = glm::perspective(glm::radians(45.0f), (float)width / height, 0.1f, 100.0f);

        glm::mat4 mvp = proj * view * model;

        
        shader.setUniformMat4("u_MVP", mvp);
      

        /*glBindVertexArray(vao);*/
       
        renderer.Draw(va, ib, shader);




        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
       

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    //glDeleteProgram(program);
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}
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
#include "Camera.h"



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

    // Variables that help the rotation of the pyramid
    //float rotation = 0.0f;
    //double prevTime = glfwGetTime();
    //glm::vec3 translation(0.0f, 1.0f, 0.0f);
    //glm::vec3 v_camPos(0.0f, -0.5f, -2.0f);
    //double lastMouseX = 0.0f, lastMouseY = 0.0f;

    /* Loop until the user closes the window */
    //while (!glfwWindowShouldClose(window))
    //{
    //    /* Render here */
    //    renderer.Clear();
    //    ImGui_ImplOpenGL3_NewFrame();
    //    ImGui_ImplGlfw_NewFrame();
    //    ImGui::NewFrame();

    //    shader.Bind();
    //    texture.Bind();
    //    shader.setUniform1i("u_Texture", 0);
    //    
    //    shader.setUniform4f("u_Color", 0.8f, 0.5f, 0.3f, 1.0f);

    //    // Simple timer
    //    double crntTime = glfwGetTime();
    //    if (crntTime - prevTime >= 1 / 60)
    //    {
    //        rotation += 0.05f;
    //        prevTime = crntTime;
    //    }

    //    // Initializes matrices so they are not the null matrix
    //    glm::mat4 model = glm::mat4(1.0f);
    //    glm::mat4 view = glm::mat4(1.0f);
    //    glm::mat4 proj = glm::mat4(1.0f);


    //    ImGui::Begin("My Gui");

    //    ImGui::Text("hello world");
    //    // Generate samples and plot them
    //    float samples[100];
    //    for (int n = 0; n < 100; n++)
    //        samples[n] = sinf(n * 0.2f + (float)ImGui::GetTime() * 1.5f);
    //    ImGui::PlotLines("Samples", samples, 100);
    //    ImGui::SliderFloat3("Translation", &translation.x, 0.0f, 1.0f);
    //    ImGui::SliderFloat3("Camera position", &v_camPos.x, -100.0f, -1.0f);
    //    ImGui::End();
    //    ImGui::Render();

    //    model = glm::rotate(model, glm::radians(rotation), translation);
    //    view = glm::translate(view,v_camPos);
    //    proj = glm::perspective(glm::radians(45.0f), (float)width / height, 0.1f, 100.0f);

    //    glm::mat4 mvp = proj * view * model;
    //    
    //    shader.setUniformMat4("u_MVP", mvp);
    //    /*glBindVertexArray(vao);*/
    //   
    //    renderer.Draw(va, ib, shader);

    //    int display_w, display_h;
    //    glfwGetFramebufferSize(window, &display_w, &display_h);
    //    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    //   
    //    /* Swap front and back buffers */
    //    glfwSwapBuffers(window);

    //    /* Poll for and process events */
    //    glfwPollEvents();
    //}

    //float rotation = 0.0f;
    //double prevTime = glfwGetTime();
    //glm::vec3 translation(0.0f, 1.0f, 0.0f);
    //glm::vec3 v_camPos(0.0f, -0.5f, -2.0f);
    //double lastMouseX = 0.0f, lastMouseY = 0.0f;
    //Camera camera(glm::vec3(1.0f));

    //while (!glfwWindowShouldClose(window)) {
    //    /* Render here */
    //    renderer.Clear();
    //    ImGui_ImplOpenGL3_NewFrame();
    //    ImGui_ImplGlfw_NewFrame();
    //    ImGui::NewFrame();

    //    // Handle mouse and keyboard input as previously
    //    double mouseX, mouseY;
    //    glfwGetCursorPos(window, &mouseX, &mouseY);

    //    //// Calculate mouse delta
    //    //float deltaX = (float)(mouseX - lastMouseX);
    //    //float deltaY = (float)(mouseY - lastMouseY);

    //    //// Update camera rotation based on mouse input
    //    //camera.rotate(deltaX, deltaY);

    //    glfwGetCursorPos(window, &mouseX, &mouseY);

    //    int rmbState = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
    //    std::cout << "RMB State: " << rmbState << std::endl;  // Debug mouse button state

    //    if (rmbState == GLFW_PRESS && !ImGui::GetIO().WantCaptureMouse) {
    //        float deltaX = (float)(mouseX - lastMouseX);
    //        float deltaY = (float)(mouseY - lastMouseY);
    //        std::cout << "Pressed RMB: " << deltaX << ", " << deltaY << std::endl;
    //        camera.rotate(deltaX, deltaY);
    //    }



    //    // Update last mouse position for next frame
    //    lastMouseX = mouseX;
    //    lastMouseY = mouseY;

    //    // Handle keyboard input for camera movement (W, A, S, D)
    //    bool moveForward = glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS;
    //    bool moveBackward = glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS;
    //    bool moveLeft = glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS;
    //    bool moveRight = glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS;

    //    // Calculate the camera movement direction
    //    glm::vec3 direction(0.0f);
    //    if (moveForward) direction += glm::vec3(0.0f, 0.0f, -1.0f);
    //    if (moveBackward) direction += glm::vec3(0.0f, 0.0f, 1.0f);
    //    if (moveLeft) direction += glm::vec3(-1.0f, 0.0f, 0.0f);
    //    if (moveRight) direction += glm::vec3(1.0f, 0.0f, 0.0f);

    //    // Update camera position based on movement
    //    camera.move(direction, 1.0f / 60.0f); // Assuming 60 FPS

    //    // Simple timer to animate the rotation
    //    double crntTime = glfwGetTime();
    //    if (crntTime - prevTime >= 1 / 60.0) {
    //        rotation += 0.05f;
    //        prevTime = crntTime;
    //    }

    //    // Initialize matrices
    //    glm::mat4 model = glm::mat4(1.0f); // Center the model at the origin
    //    glm::mat4 view = camera.getViewMatrix(); // Get the view matrix from the camera
    //    glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)width / height, 0.1f, 100.0f);

    //    // Update MVP (Model * View * Projection)
    //    glm::mat4 mvp = proj * view * model;

    //    shader.Bind();
    //    texture.Bind();
    //    shader.setUniform1i("u_Texture", 0);
    //    shader.setUniform4f("u_Color", 0.8f, 0.5f, 0.3f, 1.0f);
    //    shader.setUniformMat4("u_MVP", mvp);  // Pass the MVP matrix to the shader

    //    ImGui::Begin("My Gui");
    //    ImGui::Text("hello world");

    //    // Generate samples and plot them
    //    float samples[100];
    //    for (int n = 0; n < 100; n++)
    //        samples[n] = sinf(n * 0.2f + (float)ImGui::GetTime() * 1.5f);
    //    ImGui::PlotLines("Samples", samples, 100);

    //    // Slider controls for camera translation and position
    //    ImGui::SliderFloat3("Translation", &translation.x, 0.0f, 1.0f);
    //    ImGui::SliderFloat3("Camera position", &v_camPos.x, -100.0f, -1.0f);
    //    ImGui::End();

    //    ImGui::Render();

    //    // Apply the translation and other transformations to the model matrix
    //    model = glm::rotate(model, glm::radians(rotation), translation);
    //    view = glm::translate(view, v_camPos); // Apply camera position from sliders

    //    // Draw the object using the MVP matrix
    //    renderer.Draw(va, ib, shader);

    //    // Render ImGui
    //    int display_w, display_h;
    //    glfwGetFramebufferSize(window, &display_w, &display_h);
    //    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    //    // Swap buffers and poll events
    //    glfwSwapBuffers(window);
    //    glfwPollEvents();
    //}

float rotation = 0.0f;
double prevTime = glfwGetTime();
glm::vec3 translation(0.0f, 1.0f, 0.0f);
glm::vec3 v_camPos(0.0f, -0.5f, -2.0f);
double lastMouseX = 0.0f, lastMouseY = 0.0f;
// Initialize camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f), 5.0f, 0.1f, 5.0f);

while (!glfwWindowShouldClose(window)) {
    // Compute delta time
    double currentFrame = glfwGetTime();
    float deltaTime = static_cast<float>(currentFrame - prevTime);
    prevTime = currentFrame;

    // Clear screen
    renderer.Clear();
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // Mouse Input Handling
    double mouseX, mouseY;
    glfwGetCursorPos(window, &mouseX, &mouseY);

    int rmbState = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
    if (rmbState == GLFW_PRESS && !ImGui::GetIO().WantCaptureMouse) {
        float deltaX = static_cast<float>(mouseX - lastMouseX);
        float deltaY = static_cast<float>(mouseY - lastMouseY);
        camera.rotate(deltaX, deltaY, 0.0f, deltaTime);
    }

    lastMouseX = mouseX;
    lastMouseY = mouseY;

    // Keyboard Input Handling (Movement)
    glm::vec3 direction(0.0f);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) direction += glm::vec3(0.0f, 0.0f, -1.0f);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) direction += glm::vec3(0.0f, 0.0f, 1.0f);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) direction += glm::vec3(-1.0f, 0.0f, 0.0f);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) direction += glm::vec3(1.0f, 0.0f, 0.0f);
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) direction += glm::vec3(0.0f, 1.0f, 0.0f);  // Move Up
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) direction += glm::vec3(0.0f, -1.0f, 0.0f); // Move Down

    // Apply movement
    camera.move(direction, deltaTime);

    // Roll 
    float rollInput = 0.0f;
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) rollInput = -1.0f;  // Roll left
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) rollInput = 1.0f;   // Roll right
    camera.rotate(0.0f, 0.0f, rollInput * 30.0f, deltaTime);  // Roll 

    // Initialize matrices
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = camera.getViewMatrix();
    glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)width / height, 0.1f, 100.0f);

    // Compute final MVP matrix
    glm::mat4 mvp = proj * view * model;

    // Render scene
    shader.Bind();
    texture.Bind();
    shader.setUniform1i("u_Texture", 0);
    shader.setUniform4f("u_Color", 0.8f, 0.5f, 0.3f, 1.0f);
    shader.setUniformMat4("u_MVP", mvp);
    renderer.Draw(va, ib, shader);

    // ImGui UI
    ImGui::Begin("Camera Controls");
    ImGui::Text("Use Mouse + RMB to rotate");
    ImGui::Text("WASD - Move | Q/E - Roll | Space/LCTRL - Up/Down");

    ImGui::SliderFloat3("Camera Position", &v_camPos.x, -100.0f, 100.0f);
    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    // Swap buffers and poll events
    glfwSwapBuffers(window);
    glfwPollEvents();
}





    //glDeleteProgram(program);
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}
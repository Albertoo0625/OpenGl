//// This is a personal academic project. Dear PVS-Studio, please check it.
//
//// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
//
//#include"GL/glew.h"
//#include<glfw3.h>
//#include<iostream>
//#include<string>
//#include<fstream>
//#include<sstream>
//#include"Renderer.h"
//#include"VertexBuffer.h"
//#include"IndexBuffer.h"
//#include"VertexArray.h"
//#include"shader.h"
//#include"Texture.h"
//#include"Vendor/glm/glm.hpp"
//#include"Vendor/glm/gtc/matrix_transform.hpp"
//#include"Vendor/glm/gtc/type_ptr.hpp"
//#include"Vendor/Imgui/imgui.h"
//#include"Vendor/Imgui/imgui_impl_opengl3.h"
//#include"Vendor/Imgui/imgui_impl_glfw.h"
//#include "Camera.h"
//
//
//
//int main(void)
//{
//    GLFWwindow* window;
//    unsigned int width = 720;
//    unsigned int height = 1280;
//
//    /* Initialize the library */
//    if (!glfwInit())
//    {
//        return -1;
//    }
//
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//
//    /* Create a windowed mode window and its OpenGL context */
//    window = glfwCreateWindow(height, width, "Hello World", NULL, NULL);
//    if (!window)
//    {
//        glfwTerminate();
//        return -1;
//    }
//
//    /* Make the window's context current */
//    glfwMakeContextCurrent(window);
//
//    
//
//    ImGui::CreateContext(); 
//    ImGui_ImplGlfw_InitForOpenGL(window, true);
//    ImGui_ImplOpenGL3_Init();
//    ImGui::StyleColorsDark();
//
//    if (glewInit() == GLEW_OK) {
//        std::cout << "glew setup done" << std::endl;
//    }
//
//
//    float positions[] =
//    { //     COORDINATES     /   TexCoord  //
//        -0.5f, 0.0f,  0.5f,    	0.0f, 0.0f,       
//        -0.5f, 0.0f, -0.5f,    	1.0f, 0.0f,       
//         0.5f, 0.0f, -0.5f,    	0.0f, 0.0f,    
//         0.5f, 0.0f,  0.5f,    	1.0f, 0.0f,     
//         0.0f, 0.8f,  0.0f,    	0.5f, 1.0f
//    };
//
//    unsigned int indices[] =
//    {
//        0, 1, 2,
//        0, 2, 3,
//        0, 1, 4,
//        1, 2, 4,
//        2, 3, 4,
//        3, 0, 4
//    };
//
//    VertexArray va;
//    VertexBuffer vb(positions, sizeof(positions)); // VertexBuffer vb(positions, 4 * 4 * sizeof(float));
//    
//    VertexBufferLayout layout;
//
//    layout.push<float>(3);
//    layout.push<float>(2);
//    va.AddBuffer(vb, layout);
//
//
//    // Enables the Depth Buffer
//    glEnable(GL_DEPTH_TEST);
//    glEnable(GL_BLEND);
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//
//    IndexBuffer ib(indices, 18);
//
//
//
//    //unsigned int ibo;
//    //glGenBuffers(1, &ibo);
//    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
//    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);
//   
//    Texture texture("res/Textures/brick.png");
//  
//    Shader shader("res/shaders/Basic.shader");
//
//    Renderer renderer;
//
//
////float rotation = 0.0f;
////double prevTime = glfwGetTime();
////glm::vec3 translation(0.0f, 1.0f, 0.0f);
////glm::vec3 v_camPos(0.0f, -0.5f, -2.0f);
////double lastMouseX = 0.0f, lastMouseY = 0.0f;
////// Initialize camera
////Camera camera(glm::vec3(0.0f, 0.0f, 3.0f), 5.0f, 0.1f, 5.0f);
//
//
////while (!glfwWindowShouldClose(window)) {
////    // Compute delta time
////    double currentFrame = glfwGetTime();
////    float deltaTime = static_cast<float>(currentFrame - prevTime);
////    prevTime = currentFrame;
////
////    // Clear screen
////    renderer.Clear();
////    ImGui_ImplOpenGL3_NewFrame();
////    ImGui_ImplGlfw_NewFrame();
////    ImGui::NewFrame();
////
////    // Mouse Input Handling
////    double mouseX, mouseY;
////    glfwGetCursorPos(window, &mouseX, &mouseY);
////
////    int rmbState = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
////    if (rmbState == GLFW_PRESS && !ImGui::GetIO().WantCaptureMouse) {
////        float deltaX = static_cast<float>(mouseX - lastMouseX);
////        float deltaY = static_cast<float>(mouseY - lastMouseY);
////        camera.rotate(deltaX, deltaY, 0.0f, deltaTime);
////    }
////
////    lastMouseX = mouseX;
////    lastMouseY = mouseY;
////
////
////
////    // Keyboard Input Handling (Movement)
////    glm::vec3 direction(0.0f);
////    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) direction += glm::vec3(0.0f, 0.0f, -1.0f);
////    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) direction += glm::vec3(0.0f, 0.0f, 1.0f);
////    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) direction += glm::vec3(-1.0f, 0.0f, 0.0f);
////    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) direction += glm::vec3(1.0f, 0.0f, 0.0f);
////    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) direction += glm::vec3(0.0f, 1.0f, 0.0f);  // Move Up
////    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) direction += glm::vec3(0.0f, -1.0f, 0.0f); // Move Down
////
////    // Apply movement
////    camera.move(direction, deltaTime);
////
////    // Roll 
////    float rollInput = 0.0f;
////    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) rollInput = -1.0f;  // Roll left
////    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) rollInput = 1.0f;   // Roll right
////    camera.rotate(0.0f, 0.0f, rollInput * 30.0f, deltaTime);  // Roll 
////
////    // Initialize matrices
////    glm::mat4 model = glm::mat4(1.0f);
////    glm::mat4 view = camera.getViewMatrix();
////    glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)width / height, 0.1f, 100.0f);
////
////    // Compute final MVP matrix
////    glm::mat4 mvp = proj * view * model;
////
////    // Render scene
////    shader.Bind();
////
////    texture.Bind();
////    shader.setUniform1i("u_Texture", 0);
////    shader.setUniform4f("u_Color", 0.8f, 0.5f, 0.3f, 1.0f);
////    shader.setUniformMat4("u_MVP", mvp);
////    renderer.Draw(va, ib, shader);
////
////    // ImGui UI
////    ImGui::Begin("Camera Controls");
////    ImGui::Text("Use Mouse + RMB to rotate");
////    ImGui::Text("WASD - Move | Q/E - Roll | Space/LCTRL - Up/Down");
////
////    ImGui::SliderFloat3("Camera Position", &v_camPos.x, -100.0f, 100.0f);
////    ImGui::End();
////
////    ImGui::Render();
////    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
////
////    // Swap buffers and poll events
////    glfwSwapBuffers(window);
////    glfwPollEvents();
////}
//
//
//// Assume these are declared and initialized before the loop:
//
//// Initialize camera
//Camera camera(glm::vec3(0.0f, 0.0f, 3.0f), 5.0f, 0.1f, 5.0f);
//double prevTime = glfwGetTime();
//float rotation = 0.0f;
//glm::vec3 translation(0.0f, 1.0f, 0.0f);
//glm::vec3 v_camPos(0.0f, -0.5f, -2.0f);
//double lastMouseX = 0.0f, lastMouseY = 0.0f;
//
//while (!glfwWindowShouldClose(window)) {
//        // Clear screen
//    renderer.Clear();
//    ImGui_ImplOpenGL3_NewFrame();
//    ImGui_ImplGlfw_NewFrame();
//    ImGui::NewFrame();
//
//
//    double currentFrame = glfwGetTime();
//    float deltaTime = static_cast<float>(currentFrame - prevTime);
//    prevTime = currentFrame;
//
//    // Process mouse input for free look:
//    double mouseX, mouseY;
//    glfwGetCursorPos(window, &mouseX, &mouseY);
//    int mouseButtonState = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
//    if (mouseButtonState == GLFW_PRESS && !ImGui::GetIO().WantCaptureMouse) {
//        float deltaX = static_cast<float>(mouseX - lastMouseX);
//        float deltaY = static_cast<float>(mouseY - lastMouseY);
//        camera.rotate(deltaX, deltaY, 0.0f, deltaTime);
//    }
//    lastMouseX = mouseX;
//    lastMouseY = mouseY;
//
//    // Process keyboard input for free movement:
//    glm::vec3 movementDirection(0.0f);
//    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
//        movementDirection.z -= 1.0f; // Move forward
//    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
//        movementDirection.z += 1.0f; // Move backward
//    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
//        movementDirection.x -= 1.0f; // Move left
//    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
//        movementDirection.x += 1.0f; // Move right
//    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
//        movementDirection.y += 1.0f; // Move up
//    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
//        movementDirection.y -= 1.0f; // Move down
//    camera.move(movementDirection, deltaTime);
//
//    // Build view and projection matrices:
//    glm::mat4 view = camera.getViewMatrix();
//    glm::mat4 proj = camera.getProjectionMatrix(45.0f, (float)width / height, 0.1f, 100.0f);
//
//    // ... Render your scene using these matrices ...
//
//    glm::mat4 model = glm::mat4(1.0f);
//        
//        // Compute final MVP matrix
//        glm::mat4 mvp = proj * view * model;
//    
//        // Render scene
//        shader.Bind();
//    
//        texture.Bind();
//        shader.setUniform1i("u_Texture", 0);
//        shader.setUniform4f("u_Color", 0.8f, 0.5f, 0.3f, 1.0f);
//        shader.setUniformMat4("u_MVP", mvp);
//        renderer.Draw(va, ib, shader);
//    
//        // ImGui UI
//        ImGui::Begin("Camera Controls");
//        ImGui::Text("Use Mouse + RMB to rotate");
//        ImGui::Text("WASD - Move | Q/E - Roll | Space/LCTRL - Up/Down");
//    
//        ImGui::SliderFloat3("Camera Position", &v_camPos.x, -100.0f, 100.0f);
//        ImGui::End();
//    
//        ImGui::Render();
//        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
//    
//        // Swap buffers and poll events
//        glfwSwapBuffers(window);
//        glfwPollEvents();
//}
//
//
//    //glDeleteProgram(program);
//    ImGui_ImplOpenGL3_Shutdown();
//    ImGui_ImplGlfw_Shutdown();
//    ImGui::DestroyContext();
//    glfwTerminate();
//    return 0;
//}



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

unsigned int width = 720;
unsigned int height = 1280;

int main(void)
{
    // Initialize GLFW.
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a window.
    GLFWwindow* window = glfwCreateWindow(width, height, "Orbiting Camera", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Initialize GLEW.
    if (glewInit() != GLEW_OK) {
        std::cout << "GLEW initialization failed!" << std::endl;
        return -1;
    }
    std::cout << "GLEW initialized successfully." << std::endl;

    // Initialize ImGui.
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
    ImGui::StyleColorsDark();

    // Define vertex positions and indices.
    float positions[] =
    { //  COORDINATES         / TexCoord
        -0.5f, 0.0f,  0.5f,     0.0f, 0.0f,
        -0.5f, 0.0f, -0.5f,     1.0f, 0.0f,
         0.5f, 0.0f, -0.5f,     0.0f, 0.0f,
         0.5f, 0.0f,  0.5f,     1.0f, 0.0f,
         0.0f, 0.8f,  0.0f,     0.5f, 1.0f
    };

    unsigned int indices[] =
    {
        0, 1, 2,
        0, 2, 3,
        0, 1, 4,
        1, 2, 4,
        2, 3, 4,
        3, 0, 4
    };

    // Setup vertex array, vertex buffer and layout.
    VertexArray va;
    VertexBuffer vb(positions, sizeof(positions));
    VertexBufferLayout layout;
    layout.push<float>(3);
    layout.push<float>(2);
    va.AddBuffer(vb, layout);

    // Setup index buffer.
    IndexBuffer ib(indices, 18);

    // Enable depth testing and blending.
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Load texture and shader.
    Texture texture("res/Textures/brick.png");
    Shader shader("res/shaders/Basic.shader");
    Renderer renderer;

    // Timing variables.
    double prevTime = glfwGetTime();

    // --- Setup Orbit Camera ---
    // Define the target object position (the point you want to orbit around).
    glm::vec3 target(0.0f, 0.0f, 0.0f);
    // Create the camera. Its initial position will determine the orbit radius.
    // Here we start at (0, 0, 5) which means orbitRadius will be 5.
    Camera camera(glm::vec3(0.0f, 0.0f, 5.0f), 5.0f, 0.2f, 5.0f);

    // Variables for mouse-based free look (if you wish to mix modes).
    double lastMouseX = 0.0, lastMouseY = 0.0;

    // Main loop.
    while (!glfwWindowShouldClose(window))
    {
        double currentTime = glfwGetTime();
        float deltaTime = static_cast<float>(currentTime - prevTime);
        prevTime = currentTime;

        // Clear screen.
        renderer.Clear();

        // Start new ImGui frame.
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // --- Option 1: Mouse Free Look (Optional) ---
        // (If you want to combine free look with orbiting, you can include this.)
        double mouseX, mouseY;
        glfwGetCursorPos(window, &mouseX, &mouseY);
        int mouseButtonState = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
        if (mouseButtonState == GLFW_PRESS && !ImGui::GetIO().WantCaptureMouse)
        {
            float deltaX = static_cast<float>(mouseX - lastMouseX);
            float deltaY = static_cast<float>(mouseY - lastMouseY);
            // Here you might call camera.rotate() for free-look. For orbit mode, you may skip this.
            // camera.rotate(deltaX, deltaY, 0.0f, deltaTime);
        }
        lastMouseX = mouseX;
        lastMouseY = mouseY;

        // --- Option 2: Orbiting via Key Combinations ---
        // Use arrow keys to change orbit yaw and pitch.
        float rotationSpeed = 50.0f; // Degrees per second.
        float deltaOrbitYaw = 0.0f;
        float deltaOrbitPitch = 0.0f;

        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
            deltaOrbitYaw -= rotationSpeed * deltaTime;
        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
            deltaOrbitYaw += rotationSpeed * deltaTime;
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
            deltaOrbitPitch += rotationSpeed * deltaTime;
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
            deltaOrbitPitch -= rotationSpeed * deltaTime;

        if (deltaOrbitYaw != 0.0f || deltaOrbitPitch != 0.0f)
        {
            camera.orbitAroundTarget(target, deltaOrbitYaw, deltaOrbitPitch);
        }

        // --- Optionally, add free movement keys if you want to move the target or camera ---
        // (For an orbit camera, you often keep the target fixed.)
        // For example, you can move the target with IJKL keys, then update the camera's orbit accordingly.
        // Here we leave it static.


            // Process keyboard input for free movement:
    glm::vec3 movementDirection(0.0f);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        movementDirection.z -= 1.0f; // Move forward
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        movementDirection.z += 1.0f; // Move backward
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        movementDirection.x -= 1.0f; // Move left
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        movementDirection.x += 1.0f; // Move right
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        movementDirection.y += 1.0f; // Move up
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        movementDirection.y -= 1.0f; // Move down
    camera.move(movementDirection, deltaTime);

        // --- Build Matrices ---
        glm::mat4 view = camera.getViewMatrix();
        glm::mat4 proj = camera.getProjectionMatrix(45.0f, (float)width / height, 0.1f, 100.0f);
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 mvp = proj * view * model;

        // Render scene.
        shader.Bind();
        texture.Bind();
        shader.setUniform1i("u_Texture", 0);
        shader.setUniform4f("u_Color", 0.8f, 0.5f, 0.3f, 1.0f);
        shader.setUniformMat4("u_MVP", mvp);
        renderer.Draw(va, ib, shader);

        // Render ImGui UI.
        ImGui::Begin("Camera Controls");
        ImGui::Text("Orbit Mode: Use Arrow Keys to Rotate Around Target");
        ImGui::Text("Target Position: (%.2f, %.2f, %.2f)", target.x, target.y, target.z);
        ImGui::End();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Swap buffers and poll events.
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Cleanup ImGui and GLFW.
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}

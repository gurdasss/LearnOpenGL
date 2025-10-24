//
// Created by gurdas-satwani on 10/24/25.
//

#define GLFW_INCLUDE_NONE

#include <iostream>
#include <glad/gl.h>
#include <GLFW/glfw3.h>

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    std::cout << "Window resized!\n";
    glViewport(0, 0, width, height);
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    std::cout << "Escape Key Got Pressed. Setting the WindowShouldClose flag to GLFW_TRUE\n";
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}


int main()
{
    if (!glfwInit()) return -1;

    // After successful initialization of GLFW, now it's time for GLFW configs.
    // Request an OpenGL 3.3 (Major.Minor), core, context from GLFW.
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    constexpr short width{640};
    constexpr short height{480};
    GLFWwindow* window{glfwCreateWindow(width, height, "Hello World", nullptr, nullptr)};

    if (!window) return -1;

    glfwMakeContextCurrent(window);

    // Initialize GLAD and load all the function pointers
    gladLoadGL(glfwGetProcAddress);

    glViewport(0, 0, width, height);

    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    glfwSetKeyCallback(window, keyCallback);

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);

    glfwTerminate();
    return 0;
}

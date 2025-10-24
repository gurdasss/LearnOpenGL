// 1. Include GLAD first
#include <glad/gl.h>

// 2. Then include GLFW
#include <GLFW/glfw3.h>

#include <iostream>

int main() {
    // --- GLFW Initialization ---
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Set OpenGL version (e.g., 4.6 Core)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // --- Window Creation ---
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL with GLAD", NULL, NULL);
    if (window == NULL) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // --- GLAD Initialization ---
    // 3. Initialize GLAD *after* making the context current
    if (!gladLoaderLoadGL()) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // If you get here, GLAD and GLFW are working!
    std::cout << "GLAD and GLFW initialized successfully!" << std::endl;
    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

    // --- Main Loop ---
    while (!glfwWindowShouldClose(window)) {
        // Clear the screen
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Swap buffers and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // --- Cleanup ---
    glfwTerminate();
    return 0;
}
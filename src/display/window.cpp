#include <display/window.h>
#include <iostream>
#include <logger/log.h>

GLsizei Window::frameBufferWidth = 0;
GLsizei Window::frameBufferHeight = 0;

Window::Window(int width, int height) : width(width), height(height) {

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, 4);

    if (glfwInit() != GLFW_TRUE) {
        CORE_ERROR("Failed to intialize GLFW");
        window = NULL;
        glfwTerminate();
    } else {
        window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
    }
    
    // LEGACY 
    // glfwGetFramebufferSize(window, &frameBufferWidth, &frameBufferHeight);
    // glViewport(0, 0, frameBufferWidth, frameBufferHeight);

    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int fbW, int fbH) {
        glViewport(0, 0, fbW, fbH);
    });

    // Important for GLEW
    glfwMakeContextCurrent(window);

    // glewExperimental = gle
}

Window::~Window() {
    glfwDestroyWindow(window);
}


void Window::MainLoop() {

    
    if (!window)
    {
        glfwTerminate();
    }

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        glBegin(GL_TRIANGLES);
        glVertex2f(-0.5f, -0.5f);
        glVertex2f(0.0f, 0.5f);
        glVertex2f(0.5f, -0.5f);
        glEnd();
        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
}


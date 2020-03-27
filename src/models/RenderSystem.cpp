#include <models/RenderSystem.h>

void RenderSystem::Render() {

    // CLEAR
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);


    // END
    glfwSwapBuffers(window->GetWindow());
    glFlush();
}

RenderSystem::RenderSystem(Window* window) : window(window) {}




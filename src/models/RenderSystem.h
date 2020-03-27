#pragma once

#include <GLFW/include/glfw3.h>
#include <display/window.h>
#include <logger/log.h>

class RenderSystem {

    public:
        void Render();
        
        void Init(Window* &window) {
            if (rSystem == NULL) {
                CORE_INFO("RenderSystem Intialized");
                rSystem = new RenderSystem(window);
            }
        }
        
    private:
        RenderSystem(Window* window);
        ~RenderSystem();
        static RenderSystem* rSystem;

        Window* window;
        int fps;
}
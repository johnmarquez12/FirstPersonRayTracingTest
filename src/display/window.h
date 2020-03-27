#pragma once 

#include <GL/include/glew.h>
#include <GLFW/include/glfw3.h>

class Window {
    public:
        Window(int width, int height);
        ~Window();
        void MainLoop();

        
        inline int GetWidth() const {
            return width;
        }

        inline int GetHeight() const {
            return height;
        }

        inline GLFWwindow* GetWindow() const {
            return window;
        }

        static inline GLsizei& GetFrameBufferWidth() {
            return frameBufferWidth;
        }
        
        static inline GLsizei& GetFrameBufferHeight() {
            return frameBufferHeight;
        }

    private: 
        int width;
        int height;
        static GLsizei frameBufferWidth;
        static GLsizei frameBufferHeight;
        GLFWwindow* window;
};


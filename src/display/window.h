#include <GLFW/include/glfw3.h>
#include <GL/include/glew.h>

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
        
    private: 
        int width;
        int height;
        static int frameBufferWidth;
        static int frameBufferHeight;
        GLFWwindow* window;
};


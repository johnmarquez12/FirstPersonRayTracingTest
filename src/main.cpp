#include <iostream>
#include <display/window.h> 
#include <display/camera.h>
// #include <glm/glm.hpp>

int main() {
	Window* window = new Window(800, 600);
	Camera camera(glm::vec3(0, 0, -3), 70.0f, float(window->getWidth)/(float)(window->getHeight), 0.01f, 1000.0f);
	window->mainLoop();

	delete window;
}
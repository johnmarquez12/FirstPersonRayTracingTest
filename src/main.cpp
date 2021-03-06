#include <iostream>
#include <display/window.h> 
#include <display/camera.h>
#include <logger/log.h>
#include <memory>

int main() {

	Log::Init();
	CORE_INFO("Initializing...");
	auto window = std::make_unique<Window>(800, 600);

	Camera camera(glm::vec3(0, 0, -3), 70.0f, float(window->GetWidth())/(float)(window->GetHeight()), 0.01f, 1000.0f);
	window->MainLoop();
}
#pragma once

#include <GLFW/include/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

using namespace glm;

//float deltaTime = 0.0f;
//float lastFrame = 0.0f;

class Camera {

    public : 
        Camera(const vec3& pos, float fov, float aspect, float zNear, float zFar) {
            camPerspective = perspective(fov, aspect, zNear, zFar);
            camPosition = pos;
            camForward = vec3(0, 0, 1);
            camUp = vec3(0, 1, 0);
        }

        void processInput(GLFWwindow* window) {
            float camSpeed = 10.0f;

            if (glfwGetKey(window, GLFW_KEY_W))
                camPosition += camSpeed * camForward;
            if (glfwGetKey(window, GLFW_KEY_S))
                camPosition -= camSpeed * camForward;
            if (glfwGetKey(window, GLFW_KEY_A))
                camPosition -= normalize(cross(camForward, camUp)) * camSpeed;
            if (glfwGetKey(window, GLFW_KEY_D)) 
                camPosition += normalize(cross(camForward, camUp)) * camSpeed;
        }

        inline mat4 getViewProjection() const {
            return camPerspective * lookAt(camPosition, camPosition + camForward, camUp);
        }

    private: 
        mat4 camPerspective; 
        vec3 camPosition; 
        vec3 camForward;
        vec3 camUp;
};

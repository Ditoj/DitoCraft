#pragma once

#include<GLFW/glfw3.h>
#include<GLFW/glfw3native.h>
#include<vendor/glm/gtc/matrix_transform.hpp>
#include<functional>
#include<iostream>

namespace ditocraft {
	class Camera;
}

class ditocraft::Camera {
	private:
		bool firstMouse;
		double lastX;
		double lastY;
		int windowW;
		int windowH;
		float fov;
		float cameraSpeed;

		glm::vec3 eulerAngles;
		glm::vec3 position;
		glm::vec3 forward;
		glm::vec3 right;
		glm::vec3 up;
		glm::vec3 worldUp;
		GLFWwindow* window;
		glm::mat4 viewMat;
		glm::mat4 projMat;

	public:
		Camera(GLFWwindow* window, int ww, int wh, float fov);
		~Camera();

		void update();
		void setFOV(float fov);
		void setPosition(const glm::vec3& position);
		void setEulerAngles(const glm::vec3& angles);

		inline void setPitch(float pitch) { this->eulerAngles.x = pitch; };
		inline void setYaw(float yaw) { this->eulerAngles.x = yaw; };
		inline void setRoll(float roll) { this->eulerAngles.x = roll; };
		inline float getPitch() { return eulerAngles.x; };
		inline float getYaw() { return eulerAngles.y; };
		inline float getRoll() { return eulerAngles.z; };
		inline float getSpeed() { return cameraSpeed; };
		inline float getFOV() const { return fov; };
		inline const glm::vec3& getPosition() const { return position; };
		inline const glm::vec3& getForward() const { return forward; };
		inline const glm::vec3& getRight() const { return right; };
		inline const glm::vec3& getUp() const { return up; };
		inline const glm::vec3& getWorldUp() const { return worldUp; };
		inline const glm::mat4& getViewMat() const { return viewMat; };
		inline const glm::mat4& getProjMat() const { return projMat; };
		inline const GLFWwindow* getWindow() const { return window; };

};
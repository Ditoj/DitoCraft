#include"Camera.hpp"

namespace ditocraft {
	Camera::Camera(GLFWwindow* window, int ww, int wh, float fov) : window(window), lastX(320), lastY(240), firstMouse(true), windowW(ww), windowH(wh),
	 position(0.f, 0.f, 3.f), right(1.f, 0.f, 0.f), forward(0.f, 0.f, 1.f), up(0.f, 1.f, 0.f), worldUp(0.f, 1.f, 0.f), fov(fov), cameraSpeed(2.f) {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}

	Camera::~Camera() {

	}

	void Camera::update() {
		glfwGetWindowSize(window, &windowW, &windowH);

		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		if(xpos != lastX || ypos != lastY) {
			if(glfwGetInputMode(window, GLFW_CURSOR) != GLFW_CURSOR_DISABLED) return;

			if(firstMouse) {
				lastX = xpos;
				lastY = ypos;
				firstMouse = false;
			}

			float xoffset = xpos - lastX;
			float yoffset = lastY - ypos;
			lastX = xpos;
			lastY = ypos;
			float sensitivity = 0.1f;
			xoffset *= sensitivity;
			yoffset *= sensitivity;
			eulerAngles.y += xoffset;
			eulerAngles.x += yoffset;
			if(eulerAngles.x > 89.0f) eulerAngles.x = 89.0f;
			if(eulerAngles.x < -89.0f) eulerAngles.x = -89.0f;
			glm::vec3 direction;
			direction.x = cos(glm::radians(eulerAngles.y)) * cos(glm::radians(eulerAngles.x));
			direction.y = sin(glm::radians(eulerAngles.x));
			direction.z = sin(glm::radians(eulerAngles.y)) * cos(glm::radians(eulerAngles.x));
			forward = glm::normalize(direction);
			right = glm::normalize(glm::cross(forward, glm::vec3(0.f, 1.f, 0.f)));
			up = glm::normalize(glm::cross(right, forward));
			lastX = xpos;
			lastY = ypos;
		}

		viewMat = glm::lookAt(position, position + forward, up);
		projMat = glm::perspective(glm::radians(fov), (float) windowW/windowH, .1f, 100.f);
	}

	void Camera::setFOV(float fov) {
		if(fov < -180.f || fov > 180.f) {
			std::cout << "[Camera] Invalid FOV value.\n";
			return;
		}

		this->fov = fov;
	}

	void Camera::setPosition(const glm::vec3& position) {
		this->position.x = position.x;
		this->position.y = position.y;
		this->position.z = position.z;
	}

	void Camera::setEulerAngles(const glm::vec3& angles) {
		this->eulerAngles.x = angles.x;
		this->eulerAngles.y = angles.y;
		this->eulerAngles.z = angles.z;
	}

	/*void Camera::defaultMouseCallback(GLFWwindow* window, double xpos, double ypos) {
		if(firstMouse) {
			lastX = xpos;
			lastY = ypos;
			firstMouse = false;
		}
	
		float xoffset = xpos - lastX;
		float yoffset = lastY - ypos;
		lastX = xpos;
		lastY = ypos;

		float sensitivity = 0.1f;
		xoffset *= sensitivity;
		yoffset *= sensitivity;

		eulerAngles.x   += xoffset;
		eulerAngles.y += yoffset;

		if(eulerAngles.x > 89.0f) eulerAngles.x = 89.0f;
		if(eulerAngles.x < -89.0f) eulerAngles.x = -89.0f;

		glm::vec3 direction;
		direction.x = cos(glm::radians(eulerAngles.y)) * cos(glm::radians(eulerAngles.x));
		direction.y = sin(glm::radians(eulerAngles.x));
		direction.z = sin(glm::radians(eulerAngles.y)) * cos(glm::radians(eulerAngles.x));
		forward = glm::normalize(direction);
	}

	void Camera::defaultMouseZoomCallback(GLFWwindow* window, double xpos, double ypos) {
		std::cout << fov << '\n';
		fov -= static_cast<float>(ypos);
		if(fov < 1.f) fov = 1.f;
		if(fov > 100.f) fov = 100.f;
	}*/
}
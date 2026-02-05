#pragma once

#include"Block.hpp"
#include"BlockManager.hpp"
#include"Camera.hpp"
#include<vector>

namespace ditocraft {
	class Player;
}

class ditocraft::Player {
	private:
		Camera camera;
		Block collider;
		std::vector<ditocraft::Block*> raycastHit;

	public:
		Player(GLFWwindow* window, int windowWidth, int windowHeight, float fov);
		~Player();

		void update();
		void update(const ditocraft::BlockManager& blocks);

		std::vector<ditocraft::Block*>& shootRay(bool stop = true);
		inline Block& getCollider() { return collider; };
		inline Camera& getCamera() { return camera; };
		inline void setSpeed(const glm::vec3& speed) { collider.setSpeed(speed); };
};
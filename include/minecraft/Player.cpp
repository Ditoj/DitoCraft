#include"Player.hpp"

namespace ditocraft {
	Player::Player(GLFWwindow* window, int windowWidth, int windowHeight, float fov) : camera(window, windowWidth, windowHeight, fov) {
		collider.setSize(glm::vec3(.6f, 1.8f, .6f));
		collider.setPosition(glm::vec3(0.f, 10.f, 0.f));
	}

	Player::~Player() {

	}

	void Player::update() {
		camera.setPosition(glm::vec3(collider.getPosition().x, collider.getyMax(), collider.getPosition().z));
		camera.update();
	}

	void Player::update(const ditocraft::BlockManager& blocks) {
		camera.setPosition(glm::vec3(collider.getPosition().x, collider.getyMax(), collider.getPosition().z));
		camera.update();
		collider.update(blocks.getBlocks());
	}
}
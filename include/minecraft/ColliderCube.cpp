#include"ColliderCube.hpp"

namespace ditocraft {
	ColliderCube::ColliderCube() {

	}

	bool ColliderCube::xOverlap(const Block& b1, const Block& b2, float offset) {
		float b1Left  = b1.getxMin() + offset;
		float b1Right = b1.getxMax() + offset;
		float b2Left  = b2.getxMin();
		float b2Right = b2.getxMax();

		return (b2Left <= b1Right && b2Right >= b1Left);
	}

	bool ColliderCube::yOverlap(const Block& b1, const Block& b2, float offset) {
		float b1Left  = b1.getyMin() + offset;
		float b1Right = b1.getyMax() + offset;
		float b2Left  = b2.getyMin();
		float b2Right = b2.getyMax();

		return (b2Left <= b1Right && b2Right >= b1Left);
	}

	bool ColliderCube::zOverlap(const Block& b1, const Block& b2, float offset) {
		float b1Left  = b1.getzMin() + offset;
		float b1Right = b1.getzMax() + offset;
		float b2Left  = b2.getzMin();
		float b2Right = b2.getzMax();

		return (b2Left <= b1Right && b2Right >= b1Left);
	}

	bool ColliderCube::isCollidingWith(const Block& b1, const Block& b2, const glm::vec3& offset) {
		return xOverlap(b1, b2, offset.x) && yOverlap(b1, b2, offset.y) && zOverlap(b1, b2, offset.z);
	}

	bool ColliderCube::xWillOverlap(const Block& b1, const Block& b2, float offset) {
		float b1Left  = b1.getxMin() + offset;
		float b1Right = b1.getxMax() + offset;
		float b2Left  = b2.getxMin();
		float b2Right = b2.getxMax();

		return (b2Left <= b1Right && b2Right >= b1Left);
	}

	bool ColliderCube::yWillOverlap(const Block& b1, const Block& b2, float offset) {
		float b1Left  = b1.getyMin() + offset;
		float b1Right = b1.getyMax() + offset;
		float b2Left  = b2.getyMin();
		float b2Right = b2.getyMax();

		return (b2Left <= b1Right && b2Right >= b1Left);
	}

	bool ColliderCube::zWillOverlap(const Block& b1, const Block& b2, float offset) {
		float b1Left  = b1.getzMin() + offset;
		float b1Right = b1.getzMax() + offset;
		float b2Left  = b2.getzMin();
		float b2Right = b2.getzMax();

		return (b2Left <= b1Right && b2Right >= b1Left);
	}

	bool ColliderCube::willCollideWith(const Block& b1, const Block& b2, const glm::vec3& offset) {
		return xWillOverlap(b1, b2, b1.getxSpeed() + offset.x) && yWillOverlap(b1, b2, b1.getySpeed() + offset.y) && zWillOverlap(b1, b2, b1.getzSpeed() + offset.z);
	}

	bool ColliderCube::containsPoint(const glm::vec3& point, const Block& block) {
		return containsPoint(point, &block);
	}

	bool ColliderCube::containsPoint(const glm::vec3& point, const Block* block) {
		return (point.x >= block->getxMin() && point.x < block->getxMax())
			&& (point.y >= block->getyMin() && point.y < block->getyMax())
			&& (point.z >= block->getzMin() && point.z < block->getzMax());
	}

	bool ColliderCube::willContainPoint(const glm::vec3& point, const Block* block) {
		return (point.x >= block->getxMin() + block->getxSpeed() && point.x < block->getxMax() + block->getxSpeed())
			&& (point.y >= block->getyMin() + block->getySpeed() && point.y < block->getyMax() + block->getySpeed())
			&& (point.z >= block->getzMin() + block->getzSpeed() && point.z < block->getzMax() + block->getzSpeed());
	}
}
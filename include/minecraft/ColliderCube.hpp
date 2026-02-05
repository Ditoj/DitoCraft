#pragma once

#include"Block.hpp"

namespace ditocraft {
	class ColliderCube;
}

class ditocraft::ColliderCube {
    public:
        ColliderCube();
        ~ColliderCube();

        static bool xOverlap(const Block& b1, const Block& b2, float offset = 0.f);
		static bool yOverlap(const Block& b1, const Block& b2, float offset = 0.f);
		static bool zOverlap(const Block& b1, const Block& b2, float offset = 0.f);

		static bool isCollidingWith(const Block& b1, const Block& b2, const glm::vec3& offset = glm::vec3(0.f));

		static bool xWillOverlap(const Block& b1, const Block& b2, float offset = 0.f);
		static bool yWillOverlap(const Block& b1, const Block& b2, float offset = 0.f);
		static bool zWillOverlap(const Block& b1, const Block& b2, float offset = 0.f);

		static bool willCollideWith(const Block& b1, const Block& b2, const glm::vec3& offset = glm::vec3(0.f));

		static bool willContainPoint(const glm::vec3& point, const Block* block);
		static bool containsPoint(const glm::vec3& point, const Block& block);
		static bool containsPoint(const glm::vec3& point, const Block* block);
};
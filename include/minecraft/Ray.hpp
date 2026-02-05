#pragma once

#include<vector>
#include"Block.hpp"
#include"ColliderCube.hpp"
#include"Camera.hpp"
#include<vendor/glm/gtc/matrix_transform.hpp>

namespace ditocraft {
	class Ray;
}

struct RaycastInfo {
	public:
		ditocraft::Block* other;
		bool hit;
		glm::vec3 point;
		glm::vec3 normal;
		int index;

		RaycastInfo() : other(nullptr), hit(false), point(0.f), normal(0.f) {}

		void reset() {
			other = nullptr;
			hit = false;
			index = -1;

			point.x = 0.f;
			point.y = 0.f;
			point.z = 0.f;

			normal.x = 0.f;
			normal.y = 0.f;
			normal.z = 0.f;
		}
};

class ditocraft::Ray {
	private:
		RaycastInfo info;

	public:
		Ray();
		~Ray();

		void cast(const glm::vec3& origin, const glm::vec3& direction, const std::vector<std::unique_ptr<ditocraft::Block>>& checkList, float maxDist = 1000.f);
		void cast(const glm::vec3& origin, const glm::vec3& direction, std::unique_ptr<ditocraft::Block>& block);
		void cast(const glm::vec3& origin, const glm::vec3& direction, const ditocraft::Block* block);
		void castFromCamera(ditocraft::Camera& camera, const std::vector<std::unique_ptr<ditocraft::Block>>& checkList, float maxDist = 1000.f);
		void castFromCamera(ditocraft::Camera& camera, std::unique_ptr<ditocraft::Block>& block);

		ditocraft::Block* castCheck(const glm::vec3& origin, const glm::vec3& direction, std::vector<std::unique_ptr<ditocraft::Block>>& checkList, float maxDist = 1000.f);
		bool castCheck(const glm::vec3& origin, const glm::vec3& direction, const std::unique_ptr<ditocraft::Block>& block);
		ditocraft::Block* castFromCameraCheck(ditocraft::Camera& camera, std::vector<std::unique_ptr<ditocraft::Block>>& checkList, float maxDist = 1000.f);
		ditocraft::Block* castFromCameraCheck(ditocraft::Camera& camera, std::unique_ptr<ditocraft::Block>& block);

		inline const RaycastInfo& getRaycastInfo() { return info; }
};
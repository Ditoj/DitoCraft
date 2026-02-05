#include"Ray.hpp"

//type-safe sign() function
namespace std {
	template <typename T> int sign(T val) {
		return (T(0) < val) - (val < T(0));
	}
}

namespace ditocraft {
	Ray::Ray() {

	}

	Ray::~Ray() {

	}

	void Ray::cast(const glm::vec3& origin, const glm::vec3& direction, const std::vector<std::unique_ptr<ditocraft::Block>>& checkList, float maxDist) {
		float tmax = -1.f;
		float t;
		int index = -1;
		ditocraft::Block* result = nullptr;

		for(int i(0); i < checkList.size(); ++ i) {
			if(glm::distance(origin, checkList[i]->getPosition()) > maxDist) continue;
			if(castCheck(origin, glm::normalize(direction), checkList[i])) {
				if(result == nullptr || glm::distance(origin, checkList[i]->getPosition()) < glm::distance(origin, result->getPosition())) {
					index = i;
					result = checkList[i].get();
				}
			}
		}

		if(result != nullptr) {
			cast(origin, glm::normalize(direction), result);
			info.other = result;
			info.index = index;
		} else {
				info.reset();
			}
	}

	void Ray::cast(const glm::vec3& origin, const glm::vec3& direction, const ditocraft::Block* block) {
		info.reset();

		float t1 = (block->getxMin() - origin.x) / direction.x;
		float t2 = (block->getxMax() - origin.x) / direction.x;
		float t3 = (block->getyMin() - origin.y) / direction.y;
		float t4 = (block->getyMax() - origin.y) / direction.y;
		float t5 = (block->getzMin() - origin.z) / direction.z;
		float t6 = (block->getzMax() - origin.z) / direction.z;

		float tmin = std::max(std::max(std::min(t1, t2), std::min(t3, t4)), std::min(t5, t6));
		float tmax = std::min(std::min(std::max(t1, t2), std::max(t3, t4)), std::max(t5, t6));

		// if tmax < 0, the AABB is behind the ray origin, or no intersection
		if(tmax < 0.f || tmin > tmax) {
			info.hit = false;
			return;
		}

		// choose the nearest positive hit (tmin), otherwise use tmax
		if(tmin < 0.f) {
			info.point = origin + direction * tmax;
			info.hit = true;
		} else {
			info.point = origin + direction * tmin;
			info.hit = true;
		}

		if(info.hit) {
			float epsilon = .0001f;
			// check both max and min faces for each axis
			if(abs(info.point.x - block->getxMax()) <= epsilon) info.normal.x = 1.f;
			else if(abs(info.point.x - block->getxMin()) <= epsilon) info.normal.x = -1.f;
			else info.normal.x = 0.f;

			if(abs(info.point.y - block->getyMax()) <= epsilon) info.normal.y = 1.f;
			else if(abs(info.point.y - block->getyMin()) <= epsilon) info.normal.y = -1.f;
			else info.normal.y = 0.f;

			if(abs(info.point.z - block->getzMax()) <= epsilon) info.normal.z = 1.f;
			else if(abs(info.point.z - block->getzMin()) <= epsilon) info.normal.z = -1.f;
			else info.normal.z = 0.f;
		}
	}

	void Ray::cast(const glm::vec3& origin, const glm::vec3& direction, std::unique_ptr<ditocraft::Block>& block) {
		info.reset();

		float t1 = (block.get()->getxMin() - origin.x) / direction.x;
		float t2 = (block.get()->getxMax() - origin.x) / direction.x;
		float t3 = (block.get()->getyMin() - origin.y) / direction.y;
		float t4 = (block.get()->getyMax() - origin.y) / direction.y;
		float t5 = (block.get()->getzMin() - origin.z) / direction.z;
		float t6 = (block.get()->getzMax() - origin.z) / direction.z;

		float tmin = std::max(std::max(std::min(t1, t2), std::min(t3, t4)), std::min(t5, t6));
		float tmax = std::min(std::min(std::max(t1, t2), std::max(t3, t4)), std::max(t5, t6));

		//if tmax < 0, ray (line) the AABB is behind us
		if(tmax < 0.f) info.hit = false;

		//if tmin > tmax, ray doesn't intersect AABB
		if(tmin > tmax) info.hit = false;

		if(tmin < 0.f) {
			//return tmax
			info.point = origin + direction * tmax;
			info.hit = true;
		}

		//return tmin
		info.point = origin + direction * tmin;
		info.hit = true;
	}

	void Ray::castFromCamera(ditocraft::Camera& camera, const std::vector<std::unique_ptr<ditocraft::Block>>& checkList, float maxDist) {
		cast(camera.getPosition(), camera.getForward(), checkList, maxDist);
	}

	void Ray::castFromCamera(ditocraft::Camera& camera, std::unique_ptr<ditocraft::Block>& block) {
		cast(camera.getPosition(), camera.getForward(), block);
	}

	ditocraft::Block* Ray::castCheck(const glm::vec3& origin, const glm::vec3& direction, std::vector<std::unique_ptr<ditocraft::Block>>& checkList, float maxDist) {
		float tmax = -1.f;
		float t;
		ditocraft::Block* result = nullptr;

		for(auto& block : checkList) {
			if(glm::distance(origin, block->getPosition()) > maxDist) continue;
			if(castCheck(origin, glm::normalize(direction), block)) {
				if(result == nullptr || glm::distance(origin, block->getPosition()) < glm::distance(origin, result->getPosition())) result = block.get();
			}
		}

		return result;
	}

	bool Ray::castCheck(const glm::vec3& origin, const glm::vec3& direction, const std::unique_ptr<ditocraft::Block>& block) {
		float t1 = (block.get()->getxMin() - origin.x) / direction.x;
		float t2 = (block.get()->getxMax() - origin.x) / direction.x;
		float t3 = (block.get()->getyMin() - origin.y) / direction.y;
		float t4 = (block.get()->getyMax() - origin.y) / direction.y;
		float t5 = (block.get()->getzMin() - origin.z) / direction.z;
		float t6 = (block.get()->getzMax() - origin.z) / direction.z;

		float tmin = std::max(std::max(std::min(t1, t2), std::min(t3, t4)), std::min(t5, t6));
		float tmax = std::min(std::min(std::max(t1, t2), std::max(t3, t4)), std::max(t5, t6));

		//if tmax < 0, ray (line) the AABB is behind us
		if(tmax < 0.f) return false;

		//if tmin > tmax, ray doesn't intersect AABB
		if(tmin > tmax) return false;

		if(tmin < 0.f) return true;

		return true;
	}

	ditocraft::Block* Ray::castFromCameraCheck(ditocraft::Camera& camera, std::vector<std::unique_ptr<ditocraft::Block>>& checkList, float maxDist) {
		return castCheck(camera.getPosition(), camera.getForward(), checkList, maxDist);
	}

	ditocraft::Block* Ray::castFromCameraCheck(ditocraft::Camera& camera, std::unique_ptr<ditocraft::Block>& block) {
		return castCheck(camera.getPosition(), camera.getForward(), block) ? block.get() : nullptr;
	}
}
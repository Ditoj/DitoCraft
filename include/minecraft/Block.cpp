#include"Block.hpp"
#include"ColliderCube.hpp"

namespace ditocraft {
	Block::Block() : m_blockTextures({}), m_shader(""), position(0.f), halfExtents(.5f), speed(0.f), m_showOutline(false), type(0), resistance(240), resistanceMax(240), dropped(false), angle(0.f), savedBlock(nullptr) {
		
	}

	Block::Block(const std::vector<std::string>& texName, const std::string& shaderPath, int type) :
	m_blockTextures(texName), m_shader(shaderPath), position(0.f), halfExtents(.5f), speed(0.f), m_showOutline(false), type(type), resistance(240), resistanceMax(240), dropped(false), angle(0.f), savedBlock(nullptr) {

	}

	Block::Block(const std::vector<std::string>& texName, const std::string& shaderPath, const glm::vec3& pos, int type) :
	m_blockTextures(texName), m_shader(shaderPath), position(pos), halfExtents(.5f), speed(0.f), m_showOutline(false), type(type), resistance(240), resistanceMax(240), dropped(false), angle(0.f), savedBlock(nullptr) {


	}

	Block::~Block() {}

	void Block::setPosition(const glm::vec3& pos) {
		position.x = pos.x;
		position.y = pos.y;
		position.z = pos.z;
	}

	void Block::updatePosition(const glm::vec3& update) {
		position.x += update.x;
		position.y += update.y;
		position.z += update.z;
	}

	void Block::setSize(const glm::vec3& size) {
		this->halfExtents.x = size.x/2.f;
		this->halfExtents.y = size.y/2.f;
		this->halfExtents.z = size.z/2.f;
	}

	void Block::setSpeed(const glm::vec3& speed) {
		this->speed.x = speed.x;
		this->speed.y = speed.y;
		this->speed.z = speed.z;
	}

	void Block::update(Block& coll) {
		if(!ditocraft::ColliderCube::willCollideWith(*this, coll)) {
			position += speed;
		} else {
				if(!ditocraft::ColliderCube::willCollideWith(*this, coll, glm::vec3(speed.x, 0.f, 0.f))) position.x += speed.x;
				if(!ditocraft::ColliderCube::willCollideWith(*this, coll, glm::vec3(0.f, speed.y, 0.f))) position.y += speed.y;
				if(!ditocraft::ColliderCube::willCollideWith(*this, coll, glm::vec3(0.f, 0.f, speed.z))) position.z += speed.z;
			}
	}

	void Block::update(const std::vector<std::unique_ptr<ditocraft::Block>>& coll) {
		standingOnGround = false;

		bool updatexyz = true;
		for(const auto& blockp : coll) {
			if(ditocraft::ColliderCube::willCollideWith(*this, *blockp)) {
				if(abs(blockp->getyMax() - getyMin()) <= .1f && ditocraft::ColliderCube::xOverlap(*this, *blockp) && ditocraft::ColliderCube::zOverlap(*this, *blockp)) standingOnGround = true;

				updatexyz = false;
			}
		}

		if(updatexyz) {
			position += speed;
			return;
		}

		bool updatex = true, updatey = true, updatez = true;
		for(auto& blockp : coll) {
			if(ditocraft::ColliderCube::isCollidingWith(*this, *blockp, glm::vec3(speed.x, 0.f, 0.f))) updatex = false;
			if(ditocraft::ColliderCube::isCollidingWith(*this, *blockp, glm::vec3(0.f, speed.y, 0.f))) updatey = false;
			if(ditocraft::ColliderCube::isCollidingWith(*this, *blockp, glm::vec3(0.f, 0.f, speed.z))) updatez = false;
		}

		if(updatex) position.x += speed.x;
		if(updatey) position.y += speed.y;
		if(updatez) position.z += speed.z;
	}
}
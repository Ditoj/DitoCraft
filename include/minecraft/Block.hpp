#pragma once

#include<memory>
#include<string>
#include<vertex buffer/vertexBuffer.hpp>
#include<vertex array/vertexArray.hpp>
#include<vertex buffer layout/vertexBufferLayout.hpp>
#include<texture/texture.hpp>
#include<renderer/renderer.hpp>
#include<shader/shaderProgram.hpp>
#include"Camera.hpp"

namespace ditocraft {
    class Block;
};

class ditocraft::Block {
	private:
		std::vector<std::string> m_blockTextures;
		std::string m_shader;
		glm::vec3 position;
		glm::vec3 halfExtents;
		glm::vec3 speed;
		bool standingOnGround;
		bool m_showOutline;
		int type;
		int resistance;
		int resistanceMax;
		bool dropped;
		float angle;
		ditocraft::Block* savedBlock;

	public:
		Block();
		Block(const std::vector<std::string>& texName, const std::string& shaderPath, int type = 0);
		Block(const std::vector<std::string>& texName, const std::string& shaderPath, const glm::vec3& pos, int type = 0);

		~Block();

		void setPosition(const glm::vec3& pos);
		void updatePosition(const glm::vec3& update);
		void setSize(const glm::vec3& size);
		void setSpeed(const glm::vec3& speed);
		void update(Block& coll);
		//std::vector<ditocraft::Block*>* update(const std::vector<std::unique_ptr<ditocraft::Block>>& coll);
		void update(const std::vector<std::unique_ptr<ditocraft::Block>>& coll);
		void draw(glm::mat4 view, glm::mat4 proj);
		void draw(ditocraft::Camera& cam);

		inline void enableOutline() { m_showOutline = true; }
		inline void disableOutline() { m_showOutline = false; }
		inline float getx() const { return position.x; }
		inline float gety() const { return position.y; }
		inline float getz() const { return position.z; }
		inline float getxHalfExtents() const { return halfExtents.x; }
		inline float getyHalfExtents() const { return halfExtents.y; }
		inline float getzHalfExtents() const { return halfExtents.z; }
		inline float getxMin() const { return position.x - halfExtents.x; }
		inline float getxMax() const { return position.x + halfExtents.x; }
		inline float getyMin() const { return position.y - halfExtents.y; }
		inline float getyMax() const { return position.y + halfExtents.y; }
		inline float getzMin() const { return position.z - halfExtents.z; }
		inline float getzMax() const { return position.z + halfExtents.z; }
		inline float getxSpeed() const { return speed.x; }
		inline float getySpeed() const { return speed.y; }
		inline float getzSpeed() const { return speed.z; }
		inline const glm::vec3& getPosition() const { return position; }
		inline const glm::vec3& getHalfExtents() const { return halfExtents; }
		inline const glm::vec3& getSpeed() const { return speed; }
		inline int getType() const { return type; }
		inline bool outlineIsActive() const { return m_showOutline; }
		inline void setResistance(int resistance) { this->resistance = resistance; }

		inline const std::vector<std::string>& getTextureNames() const { return m_blockTextures; };
		inline const std::string& getShaderName() const { return m_shader; };
		inline bool isStandingOnGround() const { return standingOnGround; };
		inline bool isBeingDestroyed() const { return resistance != resistanceMax; };
		inline int getDestroyStage() const { return std::min(std::max(0, 9 - 9 * resistance / resistanceMax) - 1, 9); };
		inline void destroy(int decrease = 1) { resistance -= decrease; };
		inline bool isDestroyed() const { return resistance <= 0; };
		inline void resetDestroyStage() { resistance = resistanceMax; };
		inline bool isDropped() const { return dropped; };
		inline void setDropped(bool dropped) { this->dropped = dropped; };
		inline float getAngle() const { return angle; };
		inline void setAngle(float angle) { this->angle = angle; };
		inline void saveBlock(const std::unique_ptr<ditocraft::Block>& block) { savedBlock = block.get(); };
		inline void saveBlock(ditocraft::Block* block) { savedBlock = block; };
		inline void resetSavedBlock() { savedBlock = nullptr; };
		inline const ditocraft::Block* getSavedBlock() const { return savedBlock; };
};
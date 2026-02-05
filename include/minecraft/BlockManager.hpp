#pragma once
#define GLM_ENABLE_EXPERIMENTAL

#include"Block.hpp"
#include"Camera.hpp"
#include"Ray.hpp"
#include<vector>
#include<unordered_map>
#include<memory>
#include<algorithm>
#include<vendor/glm/gtx/norm.hpp>

namespace ditocraft {
	class Block;
	class BlockManager;
}

class ditocraft::BlockManager {
	private:
		std::vector<std::unique_ptr<ditocraft::Block>> m_blocks;
		std::vector<std::unique_ptr<ditocraft::Block>> m_droppedBlocks;
		std::vector<std::unique_ptr<texture>> m_destroyTextures;
		std::unordered_map<std::string, std::unique_ptr<texture>> m_textureNamesMap;
		std::unordered_map<std::string, std::unique_ptr<shaderProgram>> m_shaderNamesMap;
		texture m_outlineTex;
		vertexBuffer m_VBO;
		vertexArray m_VAO;
		vertexBufferLayout m_layout;
		Ray m_ray;

		float xUnit = 1.f/4.f;
		float yUnit = 1.f/3.f;
		const float vertices[288] = {
			// Back face (CCW from outside: looking at -Z)
			-0.5f, -0.5f, -0.5f, xUnit, 2.f*yUnit,      0.0f,  0.0f, -1.0f,
			-0.5f,  0.5f, -0.5f, xUnit, yUnit,          0.0f,  0.0f, -1.0f,
			0.5f,  0.5f, -0.5f,  2.f*xUnit, yUnit,      0.0f,  0.0f, -1.0f,
			0.5f,  0.5f, -0.5f,  2.f*xUnit, yUnit,      0.0f,  0.0f, -1.0f,
			0.5f, -0.5f, -0.5f,  2.f*xUnit, 2.f*yUnit,  0.0f,  0.0f, -1.0f,
			-0.5f, -0.5f, -0.5f, xUnit, 2.f*yUnit,      0.0f,  0.0f, -1.0f,
			// Front face (CCW from outside: looking at +Z)
			0.5f, -0.5f,  0.5f,  4.f*xUnit, 2.f*yUnit,  0.0f,  0.0f, 1.0f,
			0.5f,  0.5f,  0.5f,  4.f*xUnit, yUnit,      0.0f,  0.0f, 1.0f,
			-0.5f,  0.5f,  0.5f, 3.f*xUnit, yUnit,      0.0f,  0.0f, 1.0f,
			-0.5f,  0.5f,  0.5f, 3.f*xUnit, yUnit,      0.0f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f, 3.f*xUnit, 2.f*yUnit,  0.0f,  0.0f, 1.0f,
			0.5f, -0.5f,  0.5f,  4.f*xUnit, 2.f*yUnit,  0.0f,  0.0f, 1.0f,
			// Left face (CCW from outside: looking at -X)
			-0.5f, -0.5f,  0.5f, 3.f*xUnit, 2.f*yUnit, -1.0f,  0.0f,  0.0f,
			-0.5f,  0.5f,  0.5f, 3.f*xUnit, yUnit,     -1.0f,  0.0f,  0.0f,
			-0.5f,  0.5f, -0.5f, 2.f*xUnit, yUnit,     -1.0f,  0.0f,  0.0f,
			-0.5f,  0.5f, -0.5f, 2.f*xUnit, yUnit,     -1.0f,  0.0f,  0.0f,
			-0.5f, -0.5f, -0.5f, 2.f*xUnit, 2.f*yUnit, -1.0f,  0.0f,  0.0f,
			-0.5f, -0.5f,  0.5f, 3.f*xUnit, 2.f*yUnit, -1.0f,  0.0f,  0.0f,
			// Right face (CCW from outside: looking at +X)
			0.5f, -0.5f, -0.5f,  xUnit, 2.f*yUnit,       1.0f,  0.0f,  0.0f,
			0.5f,  0.5f, -0.5f,  xUnit, yUnit,           1.0f,  0.0f,  0.0f,
			0.5f,  0.5f,  0.5f,  0.f, yUnit,             1.0f,  0.0f,  0.0f,
			0.5f,  0.5f,  0.5f,  0.f, yUnit,             1.0f,  0.0f,  0.0f,
			0.5f, -0.5f,  0.5f,  0.f, 2.f*yUnit,         1.0f,  0.0f,  0.0f,
			0.5f, -0.5f, -0.5f,  xUnit, 2.f*yUnit,       1.0f,  0.0f,  0.0f,
			// Bottom face (CCW from outside: looking at -Y)
			-0.5f, -0.5f,  0.5f, xUnit, 3.f*yUnit,       0.0f, -1.0f,  0.0f,
			-0.5f, -0.5f, -0.5f, xUnit, 2.f*yUnit,       0.0f, -1.0f,  0.0f,
			0.5f, -0.5f, -0.5f,  2.f*xUnit, 2.f*yUnit,   0.0f, -1.0f,  0.0f,
			0.5f, -0.5f, -0.5f,  2.f*xUnit, 2.f*yUnit,   0.0f, -1.0f,  0.0f,
			0.5f, -0.5f,  0.5f,  2.f*xUnit, 3.f*yUnit,   0.0f, -1.0f,  0.0f,
			-0.5f, -0.5f,  0.5f, xUnit, 3.f*yUnit,       0.0f, -1.0f,  0.0f,
			// Top face (CCW from outside: looking at +Y)
			-0.5f,  0.5f, -0.5f, xUnit, 0.f,             0.0f,  1.0f,  0.0f,
			-0.5f,  0.5f,  0.5f, xUnit, yUnit,           0.0f,  1.0f,  0.0f,
			0.5f,  0.5f,  0.5f,  2.f*xUnit, yUnit,       0.0f,  1.0f,  0.0f,
			0.5f,  0.5f,  0.5f,  2.f*xUnit, yUnit,       0.0f,  1.0f,  0.0f,
			0.5f,  0.5f, -0.5f,  2.f*xUnit, 0,           0.0f,  1.0f,  0.0f,
			-0.5f,  0.5f, -0.5f, xUnit, 0.f,             0.0f,  1.0f,  0.0f
		};

	public:
		BlockManager();
		~BlockManager();

		std::unique_ptr<Block>& operator[](const int index);

		void addBlock();
		void addDrop();
		void addBlock(const std::vector<std::string>& texName, const std::string& shaderPath, int type = 0);
		void addDrop(const std::vector<std::string>& texName, const std::string& shaderPath, int type = 0);
		void addBlock(const std::vector<std::string>& texName, const std::string& shaderPath, const glm::vec3& pos, int type = 0);
		void addDrop(const std::vector<std::string>& texName, const std::string& shaderPath, const glm::vec3& pos, int type = 0);
		void addDrop(const std::unique_ptr<ditocraft::Block>& block);
		void dropBlock(int index, bool destroy = true);

		inline const std::vector<std::unique_ptr<ditocraft::Block>>& getBlocks() const { return m_blocks; }
		inline const std::unique_ptr<ditocraft::Block>& getBlock(int index) const { return m_blocks[index]; }

		void update();
		void draw(const glm::mat4& view, const glm::mat4& proj);
		void draw(const ditocraft::Camera& camera);

		void sortFromCameraView(const ditocraft::Camera& camera);
		void erase(int index);

		void    setUniform1i(const std::string& shaderName, const std::string& uname, const int i0);
		void    setUniform1f(const std::string& shaderName, const std::string& uname, const float v0);
		void    setUniform2f(const std::string& shaderName, const std::string& uname, const float v0, const float v1);
		void    setUniform2f(const std::string& shaderName, const std::string& uname, const float v[2]);
		void    setUniform2f(const std::string& shaderName, const std::string& uname, const glm::vec2& v);
		void    setUniform3f(const std::string& shaderName, const std::string& uname, const float v0, const float v1, const float v2);
		void    setUniform3f(const std::string& shaderName, const std::string& uname, const float v[3]);
		void    setUniform3f(const std::string& shaderName, const std::string& uname, const glm::vec3& v);
		void    setUniform4f(const std::string& shaderName, const std::string& uname, const float v0, const float v1, const float v2, const float v3);
		void    setUniform4f(const std::string& shaderName, const std::string& uname, const float v[4]);
		void    setUniform4f(const std::string& shaderName, const std::string& uname, const glm::vec4& v);
		void setUniformMat4f(const std::string& shaderName, const std::string& uname, const glm::mat4& mat);
		inline const vertexArray& getVAO() const { return m_VAO; };
		inline const std::unique_ptr<shaderProgram>& getShader(const std::string& name) { return m_shaderNamesMap[name]; };
};
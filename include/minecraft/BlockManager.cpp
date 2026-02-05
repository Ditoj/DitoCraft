#include"BlockManager.hpp"

namespace ditocraft {
	BlockManager::BlockManager() : m_blocks(0), m_destroyTextures(0), m_textureNamesMap(0), m_shaderNamesMap(0), m_outlineTex("images/minecraft/outline.png") {
		m_VBO.sendData(vertices, sizeof(vertices), GL_STATIC_DRAW);
		m_layout.push<GL_FLOAT>(3);
		m_layout.push<GL_FLOAT>(2);
		m_layout.push<GL_FLOAT>(3);
		m_VAO.addBuffer(m_VBO, m_layout);

		for(int i = 0; i < 10; i ++) {
			m_destroyTextures.push_back(std::make_unique<texture>("images/minecraft/destroy_stage_" + std::to_string(i) + ".png"));
		}
	}

	BlockManager::~BlockManager() {

	}

	std::unique_ptr<Block>& BlockManager::operator[](const int index) {
		return m_blocks[index];
	}

	void BlockManager::addBlock() {
		m_blocks.push_back(std::make_unique<ditocraft::Block>());
	}

	void BlockManager::addDrop() {
		m_blocks.push_back(std::make_unique<ditocraft::Block>());
		m_blocks.back()->setDropped(true);
	}

	void BlockManager::addBlock(const std::vector<std::string>& texName, const std::string& shaderPath, int type) {
		if(m_shaderNamesMap.find(shaderPath) == m_shaderNamesMap.end()) {
			shaderProgram shaderDummy;
			shaderDummy.loadShader(shaderPath);
			m_shaderNamesMap[shaderPath] = std::make_unique<shaderProgram>(shaderDummy);
		}

		for(const auto& tex : texName) {
			if(m_textureNamesMap.find(tex) == m_textureNamesMap.end()) {
				m_textureNamesMap[tex] = std::make_unique<texture>(tex);
			}
		}

		m_blocks.push_back(std::make_unique<ditocraft::Block>(texName, shaderPath, type));
	}

	void BlockManager::addDrop(const std::vector<std::string>& texName, const std::string& shaderPath, int type) {
		if(m_shaderNamesMap.find(shaderPath) == m_shaderNamesMap.end()) {
			shaderProgram shaderDummy;
			shaderDummy.loadShader(shaderPath);
			m_shaderNamesMap[shaderPath] = std::make_unique<shaderProgram>(shaderDummy);
		}

		for(const auto& tex : texName) {
			if(m_textureNamesMap.find(tex) == m_textureNamesMap.end()) {
				m_textureNamesMap[tex] = std::make_unique<texture>(tex);
			}
		}

		m_droppedBlocks.push_back(std::make_unique<ditocraft::Block>(texName, shaderPath, type));
		m_droppedBlocks.back()->setDropped(true);
	}

	void BlockManager::addBlock(const std::vector<std::string>& texName, const std::string& shaderPath, const glm::vec3& pos, int type) {
		if(m_shaderNamesMap.find(shaderPath) == m_shaderNamesMap.end()) {
			m_shaderNamesMap[shaderPath] = std::make_unique<shaderProgram>();
			m_shaderNamesMap[shaderPath]->loadShader(shaderPath);
		}

		for(const auto& tex : texName) {
			if(m_textureNamesMap.find(tex) == m_textureNamesMap.end()) {
				m_textureNamesMap[tex] = std::make_unique<texture>(tex);
			}
		}

		m_blocks.push_back(std::make_unique<ditocraft::Block>(texName, shaderPath, pos, type));
	}

	void BlockManager::addDrop(const std::vector<std::string>& texName, const std::string& shaderPath, const glm::vec3& pos, int type) {
		if(m_shaderNamesMap.find(shaderPath) == m_shaderNamesMap.end()) {
			m_shaderNamesMap[shaderPath] = std::make_unique<shaderProgram>();
			m_shaderNamesMap[shaderPath]->loadShader(shaderPath);
		}

		for(const auto& tex : texName) {
			if(m_textureNamesMap.find(tex) == m_textureNamesMap.end()) {
				m_textureNamesMap[tex] = std::make_unique<texture>(tex);
			}
		}

		m_droppedBlocks.push_back(std::make_unique<ditocraft::Block>(texName, shaderPath, pos, type));
		m_droppedBlocks.back()->setDropped(true);
	}

	void BlockManager::addDrop(const std::unique_ptr<ditocraft::Block>& block) {
		addDrop(block->getTextureNames(), block->getShaderName(), block->getPosition(), block->getType());
	}

	void BlockManager::dropBlock(int index, bool destroy) {
		addDrop(m_blocks[index]);
		if(destroy) m_blocks.erase(m_blocks.begin() + index);
	}

	void BlockManager::update() {
		for(int i(0); i < m_blocks.size(); ++ i) {
			if(m_blocks[i]->isDestroyed()) {
				dropBlock(i --);
				continue;
			}

			if(m_blocks[i]->gety() < -100.f || m_blocks[i]->gety() > 200.f) {
				m_blocks.erase(m_blocks.begin() + (i --));
				continue;
			}

			if(m_blocks[i]->getType() == 4) {
				if(m_blocks[i]->getSavedBlock() != nullptr) {
					m_ray.cast(m_blocks[i]->getPosition(), glm::vec3(0.f, -1.f, 0.f), m_blocks[i]->getSavedBlock());
					if(m_ray.getRaycastInfo().other != m_blocks[i]->getSavedBlock()) {
						m_ray.cast(glm::vec3(m_blocks[i]->getx(), m_blocks[i]->getyMin() - .1f, m_blocks[i]->getz()), glm::vec3(0.f, -1.f, 0.f), m_blocks);
						m_blocks[i]->saveBlock(m_ray.getRaycastInfo().other);
					}
				} else {
						m_ray.cast(glm::vec3(m_blocks[i]->getx(), m_blocks[i]->getyMin() - .1f, m_blocks[i]->getz()), glm::vec3(0.f, -1.f, 0.f), m_blocks);
					}

				if((m_ray.getRaycastInfo().hit && abs(m_blocks[i]->getyMin() - m_ray.getRaycastInfo().other->getyMax()) >= .04f)
				|| m_ray.getRaycastInfo().other == nullptr) {

					m_blocks[i]->updatePosition(glm::vec3(0.f, -.05f, 0.f));
				}
			}
		}

		for(int i(0); i < m_droppedBlocks.size(); ++ i) {
			if(m_droppedBlocks[i]->gety() < -100.f || m_droppedBlocks[i]->gety() > 200.f) {
				m_droppedBlocks.erase(m_droppedBlocks.begin() + (i --));
				continue;
			}

			m_ray.cast(m_droppedBlocks[i]->getPosition(), glm::vec3(0.f, -1.f, 0.f), m_blocks);
			if(!m_ray.getRaycastInfo().hit) {
				m_droppedBlocks[i]->updatePosition(glm::vec3(0.f, -.01f, 0.f));
			} else {
				if(abs(m_droppedBlocks[i]->getyMin() - m_ray.getRaycastInfo().other->getyMax()) >= .009f) {
					if(ditocraft::ColliderCube::isCollidingWith(*m_droppedBlocks[i], *m_ray.getRaycastInfo().other)) m_droppedBlocks[i]->updatePosition(glm::vec3(0.f, .01f, 0.f));
						else m_droppedBlocks[i]->updatePosition(glm::vec3(0.f, -.01f, 0.f));
				}
			}

			m_droppedBlocks[i]->setAngle(m_droppedBlocks[i]->getAngle() + .5f);
		}
	}

	void BlockManager::draw(const glm::mat4& view, const glm::mat4& proj) {
		m_VAO.bind();

		for(const auto& block : m_blocks) {
			auto& currentShader = *m_shaderNamesMap[block->getShaderName()];
			currentShader.bind();

			currentShader.setUniform1i("u_dropped", false);

			if(block->isBeingDestroyed()) {
				std::cout << m_destroyTextures.at(block->getDestroyStage()).get() << '\n';
				currentShader.setUniform1i("u_destroying", true);
				m_destroyTextures[block->getDestroyStage()]->bind(1);
				currentShader.setUniform1i("u_destroyTexture", 1);
			} else currentShader.setUniform1i("u_destroying", false);

			const std::vector<std::string>& texNames = block->getTextureNames();
			for(unsigned int i = 0; i < texNames.size(); i ++) {
				m_textureNamesMap[texNames[i]]->bind(i + 2);
				currentShader.setUniform1i("u_tex" + std::to_string(i), i + 2);
			}

			currentShader.setUniform1i("u_outline", block->outlineIsActive());

			if(block->outlineIsActive()) {
				m_outlineTex.bind(0);
				currentShader.setUniform1i("u_outlineTex", 0);
			}

			glm::mat4 model = glm::scale(glm::translate(glm::mat4(1.f), block->getPosition()), block->getHalfExtents() * 2.f);
			currentShader.setUniformMat4f("u_model", model);
			currentShader.setUniformMat4f("u_view", view);
			currentShader.setUniformMat4f("u_proj", proj);

			if(block->getType() == 2) {
				glEnable(GL_POLYGON_OFFSET_FILL);
				glPolygonOffset(-1.0f, -1.0f);
				glCullFace(GL_FRONT);
				glDrawArrays(GL_TRIANGLES, 0, 36);
				glPolygonOffset(1.0f, 1.0f);
				glCullFace(GL_BACK);
				glDrawArrays(GL_TRIANGLES, 0, 36);
				glDisable(GL_POLYGON_OFFSET_FILL);
			} else glDrawArrays(GL_TRIANGLES, 0, 36);

			block->disableOutline();
		}

		for(const auto& drop : m_droppedBlocks) {
			auto& currentShader = *m_shaderNamesMap[drop->getShaderName()];
			currentShader.bind();

			currentShader.setUniform1i("u_dropped", true);

			const std::vector<std::string>& texNames = drop->getTextureNames();
			for(unsigned int i = 0; i < texNames.size(); i ++) {
				m_textureNamesMap[texNames[i]]->bind(i);
				currentShader.setUniform1i("u_tex" + std::to_string(i), i);
			}

			glm::mat4 model = glm::rotate(glm::scale(glm::translate(glm::mat4(1.f), drop->getPosition()), drop->getHalfExtents()/2.f), glm::radians(drop->getAngle()), glm::vec3(0.f, 1.f, 0.f));
			currentShader.setUniformMat4f("u_model", model);
			currentShader.setUniformMat4f("u_view", view);
			currentShader.setUniformMat4f("u_proj", proj);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
	}

	void BlockManager::draw(const ditocraft::Camera& cam) {
		draw(cam.getViewMat(), cam.getProjMat());
	}

	void BlockManager::sortFromCameraView(const ditocraft::Camera& camera) {
		std::sort(m_blocks.begin(), m_blocks.end(), [&camera](const std::unique_ptr<ditocraft::Block>& b1, const std::unique_ptr<ditocraft::Block>& b2) {
			return glm::length2(camera.getPosition() - b1->getPosition()) > glm::length2(camera.getPosition() - b2->getPosition());
		});
	}

	void BlockManager::erase(int index) {
		if(index > 0 && index < m_blocks.size()) {
			m_blocks.erase(m_blocks.begin() + index);
			return;
		}

		std::cout << "Error during erase operation: Index out of bounds" << std::endl;
	}

	void BlockManager::setUniform1i(const std::string& shaderName, const std::string& uname, const int i0) {
		m_shaderNamesMap[shaderName]->bind();
		m_shaderNamesMap[shaderName]->setUniform1i(uname, i0);
	}

	void BlockManager::setUniform1f(const std::string& shaderName, const std::string& uname, const float v0) {
		m_shaderNamesMap[shaderName]->bind();
		m_shaderNamesMap[shaderName]->setUniform1f(uname, v0);
	}

	void BlockManager::setUniform2f(const std::string& shaderName, const std::string& uname, const float v0, const float v1) {
		m_shaderNamesMap[shaderName]->bind();
		m_shaderNamesMap[shaderName]->setUniform2f(uname, v0, v1);
	}

	void BlockManager::setUniform2f(const std::string& shaderName, const std::string& uname, const float v[2]) {
		m_shaderNamesMap[shaderName]->bind();
		m_shaderNamesMap[shaderName]->setUniform2f(uname, v);
	}

	void BlockManager::setUniform2f(const std::string& shaderName, const std::string& uname, const glm::vec2& v) {
		m_shaderNamesMap[shaderName]->bind();
		m_shaderNamesMap[shaderName]->setUniform2f(uname, v);
	}

	void BlockManager::setUniform3f(const std::string& shaderName, const std::string& uname, const float v0, const float v1, const float v2) {
		m_shaderNamesMap[shaderName]->bind();
		m_shaderNamesMap[shaderName]->setUniform3f(uname, v0, v1, v2);
	}

	void BlockManager::setUniform3f(const std::string& shaderName, const std::string& uname, const float v[3]) {
		m_shaderNamesMap[shaderName]->bind();
		m_shaderNamesMap[shaderName]->setUniform3f(uname, v);
	}

	void BlockManager::setUniform3f(const std::string& shaderName, const std::string& uname, const glm::vec3& v) {
		m_shaderNamesMap[shaderName]->bind();
		m_shaderNamesMap[shaderName]->setUniform3f(uname, v);
	}

	void BlockManager::setUniform4f(const std::string& shaderName, const std::string& uname, const float v0, const float v1, const float v2, const float v3) {
		m_shaderNamesMap[shaderName]->bind();
		m_shaderNamesMap[shaderName]->setUniform4f(uname, v0, v1, v2, v3);
	}

	void BlockManager::setUniform4f(const std::string& shaderName, const std::string& uname, const float v[4]) {
		m_shaderNamesMap[shaderName]->bind();
		m_shaderNamesMap[shaderName]->setUniform4f(uname, v);
	}

	void BlockManager::setUniform4f(const std::string& shaderName, const std::string& uname, const glm::vec4& v) {
		m_shaderNamesMap[shaderName]->bind();
		m_shaderNamesMap[shaderName]->setUniform4f(uname, v);
	}

	void BlockManager::setUniformMat4f(const std::string& shaderName, const std::string& uname, const glm::mat4& mat) {
		m_shaderNamesMap[shaderName]->bind();
		m_shaderNamesMap[shaderName]->setUniformMat4f(uname, mat);
	}
}
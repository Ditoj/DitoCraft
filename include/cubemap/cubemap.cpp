#include"cubemap.hpp"

cubemap::cubemap() {
	m_cubeTexture.bindTarget(GL_TEXTURE_CUBE_MAP, 0);
	for(unsigned int i = 0; i < 6; i ++) {
		m_cubeTexture.genTextureImage(m_face, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, false);
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

cubemap::cubemap(const std::string& path, const vertexBuffer& VBO) {
	std::string subPaths[] = {
		"/right.jpg",
		"/left.jpg",
		"/top.jpg",
		"/bottom.jpg",
		"/front.jpg",
		"/back.jpg"
	};

	m_cubeTexture.bindTarget(GL_TEXTURE_CUBE_MAP);
	for(unsigned int i = 0; i < 6; i ++) {
		m_face.filePath = path + subPaths[i];
		m_cubeTexture.genTextureImage(m_face, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, false);
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	m_layout.push<GL_FLOAT>(3);
	m_VAO.addBuffer(VBO, m_layout);
	m_shader.loadShader("shaders/cubemap.glsl");
}

void cubemap::draw(const glm::mat4& view, const glm::mat4& proj) {
	glDepthMask(GL_FALSE);
	m_shader.bind();
	m_shader.setUniformMat4f("u_view", glm::mat4(glm::mat3(view)));
	m_shader.setUniformMat4f("u_proj", proj);

	m_cubeTexture.bindTarget(GL_TEXTURE_CUBE_MAP, 1);

	m_shader.setUniform1i("u_skybox", 1);
	m_renderer.draw(m_VAO, m_shader, 0, 36);

	glDepthMask(GL_TRUE);
}
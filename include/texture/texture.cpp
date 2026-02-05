#include"texture.hpp"

texture::texture() {
	glGenTextures(1, &m_rendererId);
}

texture::texture(const std::string& path) : m_texture{ path } {
	glGenTextures(1, &m_rendererId);

	bind();
	genTextureImage(m_texture, GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	unbind();
}

texture::texture(const std::string& path, GLenum target) : m_texture{ path } {
	glGenTextures(1, &m_rendererId);

	bind(target);
	genTextureImage(m_texture, target);

	glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(target, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	unbind(target);
}

texture::texture(const std::string& path, GLint filterWrapS, GLint filterWrapT, GLint filterMin, GLint filterMag) : m_texture{ path } {
	glGenTextures(1, &m_rendererId);

	bind();
	genTextureImage(m_texture, GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, filterWrapS);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, filterWrapT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, filterWrapT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterMin);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterMag);

	unbind();
}

texture::texture(const std::string& path, GLenum target, GLint filterWrapS, GLint filterWrapT, GLint filterMin, GLint filterMag) : m_texture{ path } {
	glGenTextures(1, &m_rendererId);

	bind(target);
	genTextureImage(m_texture, target);

	glTexParameteri(target, GL_TEXTURE_WRAP_S, filterWrapS);
	glTexParameteri(target, GL_TEXTURE_WRAP_T, filterWrapT);
	glTexParameteri(target, GL_TEXTURE_WRAP_R, filterWrapT);
	glTexParameteri(target, GL_TEXTURE_MIN_FILTER, filterMin);
	glTexParameteri(target, GL_TEXTURE_MAG_FILTER, filterMag);

	unbind(target);
}

texture::~texture() {
	glDeleteTextures(1, &m_rendererId);
}

void texture::bind() const {
	glBindTexture(GL_TEXTURE_2D, m_rendererId);
}

void texture::bind(GLint slot) const {
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, m_rendererId);
}

void texture::bindTarget(GLenum target) const {
	glBindTexture(target, m_rendererId);
}

void texture::bindTarget(GLenum target, GLint slot) const {
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(target, m_rendererId);
}

void texture::unbind(GLenum target) const {
	glBindTexture(target, 0);
}

void texture::genTextureImage(imageTexture& tex, GLenum target, bool flip) {
	if(tex.filePath != "") {

		std::string ext = tex.filePath.substr(tex.filePath.find_last_of("."));
		auto channel = GL_RGB;
		if(!ext.compare(".png")) channel = GL_RGBA;

		stbi_set_flip_vertically_on_load(flip);
		tex.buffer = stbi_load(tex.filePath.c_str(), &tex.width, &tex.height, &tex.bpp, 0);

		if(tex.buffer) {
			glTexImage2D(target, 0, channel, tex.width, tex.height, 0, channel, GL_UNSIGNED_BYTE, tex.buffer);
			stbi_image_free(tex.buffer);
		} else {
				std::cout << "\nError: Failed to load texture" << std::endl;
				std::cout << stbi_failure_reason() << std::endl;
				__debugbreak();
			}
	} else {
			glTexImage2D(target, 0, GL_RGBA, tex.width, tex.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		}
}

void texture::genTextureImage(const std::string& path, GLenum target, bool flip) {
	glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	imageTexture tex;
	tex.filePath = path;

	if(tex.filePath != "") {
		stbi_set_flip_vertically_on_load(flip);
		tex.buffer = stbi_load(tex.filePath.c_str(), &tex.width, &tex.height, &tex.bpp, 0);

		if(tex.buffer) {
			glTexImage2D(target, 0, GL_RGBA, tex.width, tex.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, tex.buffer);
			stbi_image_free(tex.buffer);
		} else {
				std::cout << "\nError: Failed to load texture" << std::endl;
				std::cout << stbi_failure_reason() << std::endl;
				__debugbreak();
			}
	} else {
			glTexImage2D(target, 0, GL_RGBA, tex.width, tex.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		}
}

void texture::addToFrameBuffer(const texture& tex, GLint slot, GLenum target) const {
	tex.bindTarget(target, slot);
	glFramebufferTexture2D(target, GL_COLOR_ATTACHMENT0 + slot, GL_TEXTURE_2D, tex.m_rendererId, 0);
	tex.unbind(target);
}
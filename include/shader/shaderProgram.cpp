#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<fstream>
#include<sstream>
#include<string>
#include"shaderProgram.hpp"

shaderProgram::shaderProgram() : m_rendererId(glCreateProgram()) {};

shaderProgram::~shaderProgram() {
	glDeleteProgram(m_rendererId);
}

void shaderProgram::bind() const {
	glUseProgram(m_rendererId);
}

void shaderProgram::unbind() const {
	glUseProgram(0);
}

void shaderProgram::loadShader(const std::string& filePath) {
	m_path = filePath;

	enum class shaderType {
		NONE     = -1,
		VERTEX   =  0,
		FRAGMENT =  1,
		GEOMETRY =  2
	};

	shaderType type = shaderType::NONE;

	std::ifstream stream(filePath);
	std::string line;
	std::stringstream sStream[3];

	while(getline(stream, line)) {
		if(line.find("#shader") != std::string::npos) {
			if(line.find("vertex") != std::string::npos) {
				type = shaderType::VERTEX;
			} else if(line.find("fragment") != std::string::npos) {
					type = shaderType::FRAGMENT;
				} else if(line.find("geometry") != std::string::npos) {
						type = shaderType::GEOMETRY;
					}
		} else {
				sStream[(int) type] << line << '\n';
			}
	}

	std::string shaders[] = {
		sStream[static_cast<int>(shaderType::VERTEX)].str(),
		sStream[static_cast<int>(shaderType::FRAGMENT)].str(),
		sStream[static_cast<int>(shaderType::GEOMETRY)].str()
	};

	int glShaderType[3] = {
		GL_VERTEX_SHADER,
		GL_FRAGMENT_SHADER,
		GL_GEOMETRY_SHADER,
	};

	for(unsigned int i = 0; i < 3; i ++) {
		if(!shaders[i].empty()) {
			compileShader(shaders[i], glShaderType[i]);
		}
	}

	linkShaders();
}

void shaderProgram::compileShader(const std::string& source, GLuint type) {
	GLuint shaderId = glCreateShader(type);
	const GLchar* src = source.c_str();
	glShaderSource(shaderId, 1, &src, NULL);
	glCompileShader(shaderId);

	int success;
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
	if(success == GL_FALSE) {
		int length;
		glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &length);
		GLchar infoLog[length];
		glGetShaderInfoLog(shaderId, length, &length, infoLog);

		std::cout << "Failed to compile shader " << m_path << ". Log:\n" << infoLog << std::endl;
	}

	m_shaders.push_back({ type, shaderId });
}

void shaderProgram::linkShaders() const {
	for(const auto& shd : m_shaders) {
		glAttachShader(m_rendererId, shd.shaderId);
	}

	glLinkProgram(m_rendererId);

	int success;
	glGetProgramiv(m_rendererId, GL_LINK_STATUS, &success);
	if(!success) {
		int length;
		glGetShaderiv(m_rendererId, GL_INFO_LOG_LENGTH, &length);
		GLchar infoLog[length];
		glGetProgramInfoLog(m_rendererId, 512, NULL, infoLog);

		std::cout << "Failed to link shaders " << m_path << ". Log:\n" << infoLog << std::endl;
	}

	for(const auto& shader: m_shaders) {
		glDeleteShader(shader.shaderId);
	}
}

void shaderProgram::setUniform1i(const std::string& name, GLint v0) {
	glUniform1i(uniformGetLocation(name), v0);
}

void shaderProgram::setUniform1f(const std::string& name, GLfloat v0) {
	glUniform1f(uniformGetLocation(name), v0);
}

void shaderProgram::setUniform1fv(const std::string& name, GLsizei count, float (&v)[]) {
	glUniform1fv(uniformGetLocation(name), count, v);
}

void shaderProgram::setUniform2f(const std::string& name, GLfloat v0, GLfloat v1) {
	glUniform2f(uniformGetLocation(name), v0, v1);
}

void shaderProgram::setUniform2f(const std::string& name, const float arr[2]) {
	glUniform2f(uniformGetLocation(name), arr[0], arr[1]);
}

void shaderProgram::setUniform2f(const std::string& name, const glm::vec2& vec) {
	glUniform2f(uniformGetLocation(name), vec.x, vec.y);
}

void shaderProgram::setUniform3f(const std::string& name, float v0, float v1, float v2) {
	glUniform3f(uniformGetLocation(name), v0, v1, v2);
}

void shaderProgram::setUniform3f(const std::string& name, const float arr[3]) {
	glUniform3f(uniformGetLocation(name), arr[0], arr[1], arr[2]);
}

void shaderProgram::setUniform3f(const std::string& name, const glm::vec3& vec) {
	glUniform3f(uniformGetLocation(name), vec[0], vec[1], vec[2]);
}

void shaderProgram::setUniform4f(const std::string& name, float v0, float v1, float v2, float v3) {
	glUniform4f(uniformGetLocation(name), v0, v1, v2, v3);
}

void shaderProgram::setUniform4f(const std::string& name, const float arr[4]) {
	glUniform3f(uniformGetLocation(name), arr[0], arr[1], arr[2]);
}

void shaderProgram::setUniform4f(const std::string& name, const glm::vec4& vec) {
	glUniform3f(uniformGetLocation(name), vec[0], vec[1], vec[2]);
}

void shaderProgram::setUniformMat4f(const std::string& name, const glm::mat4& mat) {
	glUniformMatrix4fv(uniformGetLocation(name), 1, GL_FALSE, &mat[0][0]);
}

GLint shaderProgram::uniformGetLocation(const std::string& name) {
	if(m_uniformCache.find(name) != m_uniformCache.end()) return m_uniformCache[name];

	GLint location = glGetUniformLocation(m_rendererId, name.c_str());
	if(location == -1) {
		//std::cout << "Error: uniform \"" << name << "\" does not exist\n";
	} else {
			m_uniformCache[name] = location;
		}

	return location;
}

GLuint shaderProgram::getRenderer() {
	return m_rendererId;
}
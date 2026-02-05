#pragma once

#include<iostream>
#include<vector>
#include<unordered_map>

#include<vendor/glm/gtc/matrix_transform.hpp>

struct shaderObject {
    unsigned int shaderType;
    unsigned int shaderId;
};

class shaderProgram {
    private:
        unsigned int m_rendererId;
        std::vector<shaderObject> m_shaders;
        std::unordered_map<std::string, int> m_uniformCache;
        std::string m_path;

    public:
        shaderProgram();
        ~shaderProgram();

        void bind() const;
        void unbind() const;
        void loadShader(const std::string& filePath);
        void compileShader(const std::string& source, unsigned int type);
        void linkShaders() const;
        void setUniform1i(const std::string& name, int v0);
        void setUniform1f(const std::string& name, float v0);
        void setUniform1fv(const std::string& name, GLsizei count, float (&v)[]);
        void setUniform2f(const std::string& name, GLfloat v0, GLfloat v1);
        void setUniform2f(const std::string& name, const float arr[2]);
        void setUniform2f(const std::string& name, const glm::vec2& vec);
        void setUniform3f(const std::string& name, float v0, float v1, float v2);
        void setUniform3f(const std::string& name, const float arr[3]);
        void setUniform3f(const std::string& name, const glm::vec3& vec);
        void setUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
        void setUniform4f(const std::string& name, const glm::vec4& vec);
        void setUniform4f(const std::string& name, const float arr[4]);
        void setUniformMat4f(const std::string& name, const glm::mat4& mat);
        int  uniformGetLocation(const std::string& name);
        unsigned int getRenderer();
};
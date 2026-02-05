#shader vertex
#version 330 core

layout (location = 0) in vec3 in_position;
layout (location = 1) in vec3 in_normal;
layout (location = 2) in vec2 in_texCoord;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_proj;

out vec2 v_vTexCoord;
out vec3 v_vNormal;
out vec3 v_vFragPos;

void main() {
    v_vFragPos = vec3(u_model * vec4(in_position, 1.));
    v_vNormal = mat3(transpose(inverse(u_model))) * in_normal;
    v_vTexCoord = in_texCoord;
    gl_Position = u_proj * u_view * vec4(v_vFragPos, 1.);
}

#shader fragment
#version 330 core

in vec2 v_vTexCoord;
in vec3 v_vFragPos;
in vec3 v_vNormal;

uniform sampler2D u_diffuseMap;

layout (location = 0) out vec4 fragCol;

void main() {
    fragCol = texture(u_diffuseMap, v_vTexCoord);
}
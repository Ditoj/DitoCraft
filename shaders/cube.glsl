#shader vertex
#version 330 core

layout (location = 0) in vec3 in_Position;
layout (location = 1) in vec2 in_TexCoord;
layout (location = 2) in vec3 in_Normal;

out vec3 v_vFragPos;
out vec2 v_vTexCoord;
out vec3 v_vNormal;

uniform mat4 u_proj;
uniform mat4 u_view;
uniform mat4 u_model;

void main() {
	v_vFragPos = (u_model * vec4(in_Position, 1.)).xyz;
	v_vTexCoord = in_TexCoord;
	v_vNormal = mat3(transpose(inverse(u_model))) * in_Normal;

	gl_Position = u_proj * u_view * u_model * vec4(in_Position, 1.);
}

#shader fragment
#version 330 core
layout (location = 0) out vec4 fragColor;

uniform sampler2D u_texture;

in vec3 v_vFragPos;
in vec2 v_vTexCoord;
in vec3 v_vNormal;

void main() {
	fragColor = texture(u_texture, v_vTexCoord);
}
#shader vertex
#version 330 core

layout(location = 0) in vec2 in_position;
layout(location = 1) in vec2 in_texCoords;

out vec2 v_vTexCoords;

out VS_OUT {
	vec2 position;
	vec2 texCoords;
} vs_out;

void main() {
	vs_out.position = in_position;
	vs_out.texCoords = in_texCoords;
	gl_Position = vec4(in_position.xy, vec2(1.0));
}

#shader fragment
#version 330 core

in VS_OUT {
	vec2 position;
	vec2 texCoords;
} fs_in;

layout (location = 0) out vec4 fragCol;

uniform sampler2D u_crosshairTex;

void main() {
	fragCol = vec4(texture(u_crosshairTex, fs_in.texCoords));
}
#shader vertex
#version 330 core

layout (location = 0) in vec3 in_Position;
layout (location = 1) in vec2 in_TexCoord;
layout (location = 2) in vec3 in_Normal;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_proj;

out vec3 v_vPosition;
out vec2 v_vTexCoord;
out vec3 v_vNormal;

void main() {
	gl_Position = u_proj * u_view * u_model * vec4(in_Position, 1.);
	v_vPosition = in_Position;
	v_vTexCoord = in_TexCoord;
	v_vNormal   = (transpose(inverse(u_model)) * vec4(in_Normal, 1.)).xyz;
}

#shader fragment
#version 330 core

layout (location = 0) out vec4 fragCol;
in vec3 v_vPosition;
in vec2 v_vTexCoord;
in vec3 v_vNormal;

uniform sampler2D u_tex0;
uniform sampler2D u_tex1;
uniform sampler2D u_tex2;
uniform sampler2D u_tex3;
uniform sampler2D u_tex4;
uniform sampler2D u_tex5;
uniform sampler2D u_tex6;
uniform sampler2D u_tex7;
uniform sampler2D u_tex8;
uniform sampler2D u_tex9;

uniform vec3 u_lightColor;

void main() {
	//fragCol = texture(u_tex0, v_vTexCoord);
	fragCol = vec4(u_lightColor, 1.);
}
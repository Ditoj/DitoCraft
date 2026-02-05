#shader vertex
#version 330 core

layout (location = 0) in vec3 in_Position;
layout (location = 1) in vec2 in_TexCoord;
layout (location = 2) in vec3 in_Normal;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_proj;

out VS_OUT {
	vec3 position;
	vec2 texCoord;
	vec3 normal;
} vs_out;

void main() {
	vec4 vertexPosition = u_model * vec4(in_Position, 1.);
	gl_Position = u_proj * u_view * vertexPosition;

	vs_out.position = vertexPosition.xyz;
	vs_out.texCoord = vec2(in_TexCoord.x, 1. - in_TexCoord.y);
	vs_out.normal   = normalize(mat3(transpose(inverse(u_model))) * in_Normal);
}

#shader fragment
#version 330 core

layout (location = 0) out vec4 fragCol;

in VS_OUT {
	vec3 position;
	vec2 texCoord;
	vec3 normal;
} fs_in;

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

uniform vec3 u_lightPos;
uniform vec3 u_cameraPos;

uniform bool u_outline;
uniform sampler2D u_outlineTex;

uniform bool u_destroying;
uniform sampler2D u_destroyTexture;

uniform bool u_dropped;

void main() {
	if(!u_dropped) {
		if(u_outline) {
			vec4 outlineTextureSample = texture(u_outlineTex, fs_in.texCoord);
			if(outlineTextureSample.a == 1.) {
				fragCol = vec4(1.);
				return;
			}
		}

		if(u_destroying) {
			vec4 destroyTextureSample = texture(u_destroyTexture, fs_in.texCoord);
			if(destroyTextureSample.a == 1.) {
				fragCol = destroyTextureSample;
				return;
			}
		}
	}

	vec4 baseCol = texture(u_tex0, fs_in.texCoord);

	if(baseCol.a == 0.) discard;

	vec4 specularTex = texture(u_tex1, fs_in.texCoord);
	vec3 ambient = vec3(.4, .4, .4) * baseCol.rgb;

	vec3 fragToLight = normalize(u_lightPos - fs_in.position);
	vec3 lightReflect = reflect(fragToLight, fs_in.normal);
	vec3 fragToCam = normalize(u_cameraPos - fs_in.position);

	vec3 diffuse = max(0., dot(fs_in.normal, fragToLight)) * baseCol.rgb * .7;

	vec3 specular = /*pow(max(.00001, dot(lightReflect, -fragToCam)), 16.) * specularTex.rgb*/vec3(0.);

	fragCol = vec4(ambient + diffuse + specular, 1.);
}
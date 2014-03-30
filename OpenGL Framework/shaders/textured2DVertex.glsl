#version 330 core

in vec3 position;
in vec2 vertexUV;

out vec2 UV;

uniform mat4 M;

void main() {
	vec4 v = vec4(position,1);
	gl_Position = M * v;
	UV = vertexUV;
}
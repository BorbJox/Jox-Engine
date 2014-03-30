#version 330 core

in vec3 position;
in vec3 color;

out vec3 fragmentColor;

uniform mat4 M;

void main() {
	vec4 v = vec4(position,1);
	gl_Position = M * v;
	fragmentColor = color;
}
#version 330 core

in vec3 position;
in vec3 colour;
in vec2 UV;

out vec3 fragmentColour;
out vec2 fragmentUV;

uniform mat4 modelTransform;

void main() {
	vec4 localSpace = vec4(position,1);
	gl_Position = modelTransform * localSpace;
	fragmentColour = colour;
	fragmentUV = UV;
}

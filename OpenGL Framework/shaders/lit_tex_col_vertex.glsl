#version 330 core

//Diffuse lighting only
in vec3 position;
in vec3 normal;
in vec3 colour;
in vec2 UV;

out vec3 fragmentColour;
out vec2 fragmentUV;
out float lightIntensity;

uniform mat4 modelTransform;
univorm mat4 MVP;
uniform vec3 lightPosition;

void main() {
	vec4 localSpace = vec4(position,1);
	lightNormal = normalize(lightPosition - (modelTransform * localSpace));
	gl_Position = MVP * localSpace;
	lightIntensity = max(dot(normal, lightNormal), 0.0);
	fragmentColour = colour;
	fragmentUV = UV;
}

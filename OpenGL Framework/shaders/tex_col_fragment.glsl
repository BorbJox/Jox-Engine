#version 330 core

in vec3 fragmentColour;
in vec2 fragmentUV;

out vec3 outColour;

uniform sampler2D textureSampler;
uniform float colourAmount;

void main() {
	textureColour = texture(textureSampler, fragmentUV).rgb;
	outColour = mix(fragmentColour, textureColour, colourAmount);
}

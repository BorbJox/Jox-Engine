#version 330
	
	in vec3 LightIntensity;
	in vec2 UV;
	
	uniform sampler2D textureSampler;
	
	layout( location = 0 ) out vec4 FragColor;
	
	void main() {
		FragColor = vec4(LightIntensity, 1.0);
	}	
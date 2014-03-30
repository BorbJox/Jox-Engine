#version 330 core

in vec2 UV;
in vec3 posWorld;
in vec3 normalView;
in vec3 eyeDirectionView;
in vec3 lightDirectionView;

out vec3 color;

uniform sampler2D textureSampler;
uniform vec3 lightPosWorld;
uniform vec3 lightColour;
uniform float lightPower;

void main() {


	vec3 materialDiffuseColour = texture2D(textureSampler, UV).rgb;
	vec3 materialAmbientColour = vec3(0.05,0.05,0.05) * materialDiffuseColour;
	vec3 materialSpecularColour = vec3(0.3,0.3,0.3);
	
	float distance = length(lightPosWorld - posWorld);
	
	vec3 n = normalize(normalView);
	vec3 l = normalize(lightDirectionView);
	
	float cosTheta = clamp(dot(n,l),0,1);
	
	// Eye vector
	vec3 E = normalize(eyeDirectionView);
	// Reflection vector
	vec3 R = reflect(-l,n);
	
	float cosAlpha = clamp(dot(E,R),0,1);
	
	color = materialAmbientColour + materialDiffuseColour * lightColour * lightPower * cosTheta / (distance*distance) + materialSpecularColour * lightColour * lightPower * pow(cosAlpha,5) / (distance*distance);

}
#version 330 core

in vec3 position;
in vec2 vertexUV;
in vec3 normal;

out vec2 UV;
out vec3 posWorld;
out vec3 normalView;
out vec3 eyeDirectionView;
out vec3 lightDirectionView;

uniform mat4 MVP;
uniform mat4 V;
uniform mat4 M;
uniform vec3 lightPosWorld;

void main() {

	
	vec4 v = vec4(position,1);
	gl_Position = MVP * v;
	
	UV = vertexUV;
	
	posWorld = (M * vec4(position,1)).xyz;
	
	vec3 posView = (V * M * vec4(position,1)).xyz;
	eyeDirectionView = vec3(0,0,0) - posView;
	
	vec3 lightPosView = (V * vec4(lightPosWorld,1)).xyz;
	lightDirectionView = lightPosView + eyeDirectionView;
	
	//Won't work if scaled by M!
	normalView = (V * M * vec4(normal,0)).xyz;

}
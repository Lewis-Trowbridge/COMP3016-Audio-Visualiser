
#version 400 core

layout( location = 0 ) in vec3 vPosition;
layout( location = 1 ) in vec4 vColour;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in vec3 vNormal;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float scale;

uniform vec3 ambient;

out vec4 fragColour;
out vec2 TexCoord;
void
main()
{
	float ambientStrength = 0.9;
	vec3 alteredAmbient = ambientStrength * ambient;
	fragColour = vec4((alteredAmbient * vec3(max(0.3, scale), 0.0, 0.0)), 1.0);

	gl_Position = projection * view * model * vec4(vPosition,1.0);
	TexCoord = aTexCoord;
}

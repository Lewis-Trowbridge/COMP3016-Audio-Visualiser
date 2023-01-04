#version 400 core

layout ( location = 0 ) in vec3 vPosition;
layout ( location = 1 ) in vec2 aTexCoord;
layout ( location = 2 ) in vec3 vNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float scale;

out vec4 fragColour;
out vec2 texCoord;
out vec3 fragPos;  
out vec3 normal;

void
main()
{
	// Generate colour value from scale
	fragColour = vec4(max(0.5, scale), 0.2, 0.2, 1.0);

	gl_Position = projection * view * model * vec4(vPosition, 1.0);
	texCoord = aTexCoord;
	fragPos = vec3(model * vec4(vPosition, 1.0));
    normal = vNormal;
}

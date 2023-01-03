
#version 400 core

layout( location = 0 ) in vec3 vPosition;
layout( location = 1 ) in vec4 vColour;
layout (location = 2) in vec2 aTexCoord;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float scale;

out vec4 fragColour;
out vec2 TexCoord;
void
main()
{
    gl_Position = projection * view * model * vec4 (vPosition,1.0);
	fragColour = vec4(max(0.2, scale), 0.0, 0.0, 1.0);
	TexCoord = aTexCoord;
}

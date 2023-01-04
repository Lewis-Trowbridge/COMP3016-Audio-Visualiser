
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
uniform vec3 lightPos;
uniform vec3 diffuseColour;
uniform vec3 specularColour;
uniform float shininess;

out vec4 fragColour;
out vec2 TexCoord;
void
main()
{
	float ambientStrength = 0.9;
	vec3 alteredAmbient = ambientStrength * ambient;

	mat4 modelView = view * model;
	vec4 viewSpacePos = modelView * vec4(vPosition, 1.0);

	vec3 viewSpaceNormal = mat3(modelView) * vNormal;
	vec3 viewSpaceLight = lightPos - viewSpacePos.xyz;
	vec3 viewSpaceView = -viewSpacePos.xyz;

	viewSpaceNormal = normalize(viewSpaceNormal);
	viewSpaceLight = normalize(viewSpaceLight);
	viewSpaceView = normalize(viewSpaceView);

	vec3 reflection = reflect(-viewSpaceLight, viewSpaceNormal);
	
	vec3 diffuse = max(0.0, dot(viewSpaceNormal, viewSpaceLight)) * diffuseColour;
	vec3 specular = pow(max(dot(reflection, viewSpaceView), 0.0), shininess) * specularColour;

	vec4 generatedColour = vec4(max(0.5, scale), 0.2, 0.2, 1.0);


	fragColour = (vec4(alteredAmbient, 1.0) + vec4(diffuse, 1.0)) * generatedColour;

	gl_Position = projection * viewSpacePos;
	TexCoord = aTexCoord;
}

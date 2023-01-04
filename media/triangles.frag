#version 450 core

out vec4 fColor;
in vec4 fragColour;
in vec2 texCoord;
in vec3 fragPos;
in vec3 normal;


uniform sampler2D ourTexture;
uniform vec3 ambient;
uniform vec3 lightPos;
uniform vec3 diffuseColour;
uniform vec3 specularColour;
uniform float shininess;


void main()
{

	float ambientStrength = 0.9;
	vec3 alteredAmbient = ambientStrength * ambient;

	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(lightPos - fragPos);  

	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * diffuseColour;

	vec3 viewDir = normalize(lightPos - fragPos);
	vec3 reflectDir = reflect(-lightDir, norm);

	float specularStrength = 0.5;
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
	vec3 specular = specularStrength * spec * specularColour;  

	fColor = texture(ourTexture, texCoord) * (vec4(alteredAmbient, 1.0) + vec4(diffuse, 1.0) + vec4(specular, 1.0)) * fragColour;
	
}

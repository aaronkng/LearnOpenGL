#version 330 core 
out vec4 FragColor;

in vec3 v_FragPos;
in vec3 v_LightPos;
in vec3 v_ViewPos;
in vec3 v_Normal;

uniform vec3 objectColor;
uniform vec3 lightColor;

void main()
{
	// ambient 
	float ambientStrength = 0.1f;
	vec3 ambient = ambientStrength * lightColor;

	// difuse
	vec3 norm = normalize(v_Normal);
	vec3 lightDir = normalize(v_LightPos - v_FragPos);
	float diff = max(dot(norm, lightDir), 0.0f);
	vec3 diffuse = diff * lightColor;

	// specular 
	float specularStrength = 0.5f;
	vec3 viewDir = normalize(v_ViewPos - v_FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 32);
	vec3 specular = specularStrength * spec * lightColor;

	vec3 result = (ambient + diffuse + specular) * objectColor;
	FragColor = vec4(result, 1.0f);
}
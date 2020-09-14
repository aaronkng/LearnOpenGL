#version 330 core 
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;

out vec3 Color;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	// View space data
	vec3 v_FragPos = vec3(view * model * vec4(aPos, 1.0f));
	vec3 v_LightPos = vec3(view * model * vec4(lightPos, 1.0f));
	vec3 v_ViewPos = vec3(view * model * vec4(viewPos, 1.0f));
	vec3 v_Normal = mat3(transpose(inverse(view * model))) * aNormal;

	// ambient 
	float ambientStrength = 0.1f;
	vec3 ambient = ambientStrength * lightColor;

	// diffuse 
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

	Color = (ambient + diffuse + specular) * objectColor;
	gl_Position = projection * view * model * vec4(aPos, 1.0f);
}
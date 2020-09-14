#version 330 core 
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;

out vec3 v_FragPos;
out vec3 v_LightPos;
out vec3 v_ViewPos;
out vec3 v_Normal;

uniform vec3 lightPos;
uniform vec3 viewPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	v_FragPos = vec3(view * model * vec4(aPos, 1.0f));
	v_LightPos = vec3(view * vec4(lightPos, 1.0f));
	v_ViewPos = vec3(view * model * vec4(viewPos, 1.0f));
	v_Normal = mat3(transpose(inverse(view * model))) * aNormal;

	gl_Position = projection * view * model * vec4(aPos, 1.0f);
}
#version 330 core 

out vec4 FragColor;

uniform float u_FragColor;

void main()
{
	FragColor = vec4(0.0f, u_FragColor, 0.0f, 1.0f);
}
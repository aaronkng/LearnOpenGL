#version 330 core 
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D u_texture_0;
uniform sampler2D u_texture_1;
uniform float mixFloat; 

void main()
{
	FragColor = mix(texture(u_texture_0, TexCoord), texture(u_texture_1, TexCoord), mixFloat);
}
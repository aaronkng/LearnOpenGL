#version 330 core 
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D u_texture_0;
uniform sampler2D u_texture_1;

void main()
{
	vec2 newTexCoord = TexCoord * 2.0f;
	FragColor = mix(texture(u_texture_0, TexCoord), texture(u_texture_1, newTexCoord), 0.2f);
}
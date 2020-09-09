#version 450 core
uniform sampler2D Main_Tex;
uniform vec3 Color;
out vec4 FragColor;
in vec2 TexCoord;
void main()
{
	
	FragColor = vec4(Color, 0.9);

}
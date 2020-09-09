#version 450 core
uniform sampler2D Main_Tex;

out vec4 FragColor;
in vec2 TexCoord;
void main()
{
	
	vec3 color = vec3(219.0/255.0, 188.0/255.0, 33.0/255.0);
	vec2 newUV = vec2(TexCoord.x * (3307.0/300.0), TexCoord.y);
	vec3 bg = vec3(0.7, 0.7, 0.7);
	vec4 text = texture2D(Main_Tex, TexCoord);
	FragColor = text;

	
	//FragColor = vec4(1.0);

}
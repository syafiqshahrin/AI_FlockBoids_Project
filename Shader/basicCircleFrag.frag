#version 450 core
uniform sampler2D Main_Tex;

out vec4 FragColor;
in vec2 TexCoord;
void main()
{
	

	vec2 center = vec2(0.5, 0.5);
	float dist = distance(TexCoord, center);
	float radius = 0.3;
	float c = step(dist, radius);

	FragColor = vec4(vec3(c), 1.0);
	if(c < 1.0)
	{
		FragColor = vec4(vec3(c), 0.0);
	}

}
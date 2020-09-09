#version 450 core
uniform sampler2D Main_Tex;

out vec4 FragColor;
in vec2 TexCoord;
in vec4 Status;
in vec2 Status2;
void main()
{
	
	vec3 obstacleCol = vec3(0.3, 0.3, 0.3);
	vec3 pathCol = vec3(1.0, 1.0, 0.0);
	vec3 visitedCol = vec3(0.1, 0.8, 1.0);
	vec3 inOpenListCol = vec3(1.0, 0.5, 0.0);
	vec3 startCol = vec3(0.0, 1.0, 0.0);
	vec3 endCol = vec3(1.0, 0.0, 0.0);
	vec3 color;
	if(Status.x > 0.0)
	{
		color = obstacleCol;
	
	}else
	{
		if(Status.y  > 0)
		{
			color = startCol;;
		}
		else if(Status.z  > 0)
		{
			color = endCol;
		}
		else if(Status.w > 0)
		{
			float c = 0.5;
			float r = 0.4;
			float d  = distance(vec2(c),TexCoord);
			c = step(d, r);
			color = vec3(c) * pathCol;
		}
		else if(Status2.x > 0)
		{
			float c = 0.5;
			float r = 0.4;
			float d  = distance(vec2(c),TexCoord);
			c = step(d, r);
			color = vec3(c) * visitedCol;
		}
		else if(Status2.y > 0)
		{
			float c = 0.5;
			float r = 0.4;
			float d  = distance(vec2(c),TexCoord);
			c = step(d, r);
			color = vec3(c) * inOpenListCol;
		}
		else
		{
			float c = 0.5;
			float r = 0.4;
			float d  = distance(vec2(c),TexCoord);
			c = step(d, r);
			color = vec3(c);
		}
	
	}
	FragColor = vec4(color, 1.0);
	
	//FragColor = vec4(1.0);
}
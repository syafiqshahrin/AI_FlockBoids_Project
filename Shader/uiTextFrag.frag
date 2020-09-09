#version 450 core
uniform sampler2D Main_Tex;
uniform float fractVal;
uniform float intVal;
out vec4 FragColor;
in vec2 TexCoord;
void main()
{
	vec3 color = vec3(219.0/255.0, 188.0/255.0, 33.0/255.0);
	vec4 bg = vec4(0.6, 0.6, 0.6, 0.9);
	vec2 newUV;
	float textureCharOffset = (1.0/12.0);
	newUV.x = (TexCoord.x / 4.0);
	newUV.y = TexCoord.y;
	vec4 text;

	if(newUV.x >= 0.0 && newUV.x < (1.0/12.0))
	{
		
		vec2 newUV2 = newUV;
		newUV2.x += ((intVal + 2.0) * textureCharOffset);
		text = texture2D(Main_Tex, newUV2);
		
		//text = vec4(1.0,0.0,0.0,1.0);
	}
	else if(newUV.x >= (1.0/12.0) && newUV.x < (1.0/6.0))
	{
		
		vec2 newUV2 = newUV;
		newUV2.x = (1.0 * textureCharOffset) + (newUV.x - (1.0/12.0));
		text = texture2D(Main_Tex, newUV2);
		
		//text = vec4(0.0,1.0,0.0,1.0);
	}
	else if(newUV.x >= (1.0/6.0) && newUV.x < (1.0/4.0))
	{
		
		vec2 newUV2 = newUV;
		newUV2.x = ((fractVal + 2.0) * textureCharOffset)  + (newUV.x - (1.0/6.0));
		text = texture2D(Main_Tex, newUV2);
		
		//text = vec4(0.0,0.0,1.0,1.0);
	}

	FragColor.rgb = text.rgb;
	FragColor.a = text.a;


}
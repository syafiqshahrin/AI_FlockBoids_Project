#version 450 core
layout (location = 0) in vec3 vPos;
layout (location = 1) in vec2 vTexCoord;
uniform mat4 uModelMatrix;
uniform mat4 uOrthoModelMatrix;
out vec2 TexCoord;
void main()
{
	gl_Position = uOrthoModelMatrix * vec4(vPos.x, vPos.y, vPos.z, 1.0);
	TexCoord = vTexCoord;
}
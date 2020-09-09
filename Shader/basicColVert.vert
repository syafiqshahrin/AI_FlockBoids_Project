#version 450 core
layout (location = 0) in vec3 vPos;
layout (location = 1) in vec2 vTexCoord;
uniform mat4 uModelMatrix;

uniform mat4 uOrthoModelMatrix;
out vec2 TexCoord;

mat4 scaleMat(vec3 s)
{
    return mat4( s.x, 0.0, 0.0, 0.0,
                   0.0,  s.y, 0.0, 0.0,
                   0.0, 0.0,  s.z, 0.0,
                   0.0, 0.0, 0.0, 1.0);
}
void main()
{
	gl_Position = uOrthoModelMatrix * vec4(vPos.x, vPos.y, vPos.z, 1.0);
	TexCoord = vTexCoord;

}
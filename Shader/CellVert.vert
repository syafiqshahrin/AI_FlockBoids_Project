#version 450 core
layout (location = 0) in vec3 vPos;
layout (location = 1) in vec2 vTexCoord;
layout (location = 2) in mat4 cMat;
layout (location = 6) in vec4 cStatus;
layout (location = 7) in vec2 cStatus2;
//uniform mat4 uModelMatrix;
uniform int IsHovered;
//uniform mat4 uOrthoModelMatrix;
out vec2 TexCoord;
out vec4 Status;
out vec2 Status2;
mat4 scaleMat(vec3 s)
{
    return mat4( s.x, 0.0, 0.0, 0.0,
                   0.0,  s.y, 0.0, 0.0,
                   0.0, 0.0,  s.z, 0.0,
                   0.0, 0.0, 0.0, 1.0);
}
void main()
{
	gl_Position = cMat * vec4(vPos.x, vPos.y, vPos.z, 1.0);
	TexCoord = vTexCoord;
    Status = cStatus;
    Status2 = cStatus2;

}
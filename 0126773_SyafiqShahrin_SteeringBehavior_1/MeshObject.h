#pragma once

class Shader;
struct Vector3;
struct Transform;


enum MeshType {TRIANGLE, QUAD};

class MeshObject{
public:

private:
	//store mesh data
	//Quad data
	
	GLfloat m_meshQuadVertices[20] = {
		-1.0f, -1.0f, 0.0f, //position
		0.0f, 0.0f,  //Tex Coord
		-1.0f, 1.0f, 0.0f, //position
		0.0f, 1.0f,  //Tex Coord
		1.0f, -1.0f, 0.0f, //position
		1.0f, 0.0f, //Tex Coord
		1.0f, 1.0f, 0.0f, //position
		1.0f, 1.0f //Tex Coord
	};
	
	GLint m_vertexQuadIndices[6] =
	{
		0, 1, 2,
		3, 2, 1
	};
	
	//Triangle Data
	GLfloat m_meshTriVertices[15] = {
	-1.0f, -1.0f, 0.0f, //position
	0.0f, 0.0f,  //Tex Coord
	-1.0f, 1.0f, 0.0f, //position
	0.0f, 1.0f,  //Tex Coord
	1.5f, 0.0f, 0.0f, //position
	1.0f, 0.0f, //Tex Coord
	};

	GLint m_vertexTriIndices[3] =
	{
		0, 1, 2,
	};

	MeshType meshType;

	GLuint VAO;
	GLuint VBO;
	GLuint EBO;
	GLuint MBO;
	GLuint S3BO;
	GLuint S2BO;
	int size;
	int totalVertices;
	void InitQuad();
	void InitTriangle();

public:
	MeshObject();
	MeshObject(MeshType mt);
	MeshObject(bool i, int s);
	~MeshObject();
	//Draw mesh
	void DrawMesh();
	void SetInstanceSize(int s, int sY);

	void InitInstance(std::vector<float> matVec);
	void SendVec4(std::vector<float> vec4D);
	void SendVec2(std::vector<float> vec2D);
	bool instanced;
	//Change Shader

};


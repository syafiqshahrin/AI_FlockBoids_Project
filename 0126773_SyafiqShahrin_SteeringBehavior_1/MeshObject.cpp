#include <glad/glad.h>
#include <glfw3.h>
#include <iostream>
#include <vector>
#include <string>
#include "Matrix.h"
#include "Vector.h"
#include "Utility.h"
#include "Shader.h"
#include "MeshObject.h"


MeshObject:: MeshObject(bool i, int s)
{
	instanced = instanced;
	size = s;
	InitQuad();
}

MeshObject::MeshObject()
{
	instanced = false;
	size = 0;
	InitQuad();
}

MeshObject::MeshObject(MeshType mt)
{
	instanced = false;
	size = 0;
	meshType = mt;
	if (meshType == TRIANGLE)
	{
		InitTriangle();
	}
	else
	{
		InitQuad();
	}
}

void MeshObject::InitQuad()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_meshQuadVertices), m_meshQuadVertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_vertexQuadIndices), m_vertexQuadIndices, GL_STATIC_DRAW);

	//linking vertex attribute for vertex pos
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);

	//linking vertex attribute for vertex color
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(0 + 3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	//unbinding the buffers
	glBindVertexArray(0);
	//unbind vertex array first before unbind the element buffer/vbo
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	totalVertices = 6;
}
void MeshObject::InitTriangle()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_meshTriVertices), m_meshTriVertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_vertexTriIndices), m_vertexTriIndices, GL_STATIC_DRAW);

	//linking vertex attribute for vertex pos
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);

	//linking vertex attribute for vertex color
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(0 + 3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	//unbinding the buffers
	glBindVertexArray(0);
	//unbind vertex array first before unbind the element buffer/vbo
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	totalVertices = 3;
}
void MeshObject::InitInstance(std::vector<float> matVec)
{

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteBuffers(1, &MBO);

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glGenBuffers(1, &MBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_meshQuadVertices), m_meshQuadVertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_vertexQuadIndices), m_vertexQuadIndices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, MBO);
	glBufferData(GL_ARRAY_BUFFER, matVec.size() * sizeof(float), &matVec.front(), GL_STATIC_DRAW);
	//linking vertex attribute for vertex pos
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);

	//linking vertex attribute for vertex color
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(0 + 3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	//glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ARRAY_BUFFER, MBO);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 4 * (4 * sizeof(GLfloat)), (void*)0);
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 4 * (4 * sizeof(GLfloat)), (void*)(1 * (4 * sizeof(GLfloat))));
	glEnableVertexAttribArray(3);

	glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 4 * (4 * sizeof(GLfloat)), (void*)(2 * (4 * sizeof(GLfloat))));
	glEnableVertexAttribArray(4);

	glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 4 * (4 * sizeof(GLfloat)), (void*)(3 * (4 * sizeof(GLfloat))));
	glEnableVertexAttribArray(5);

	glVertexAttribDivisor(2, 1);	
	glVertexAttribDivisor(3, 1);	
	glVertexAttribDivisor(4, 1);	
	glVertexAttribDivisor(5, 1);	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//unbinding the buffers
	glBindVertexArray(0);
	//unbind vertex array first before unbind the element buffer/vbo
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}
void MeshObject::SendVec4(std::vector<float> vec4D)
{
	glDeleteBuffers(1, &S3BO);
	glGenBuffers(1, &S3BO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, S3BO);
	glBufferData(GL_ARRAY_BUFFER, vec4D.size() * sizeof(float), &vec4D.front(), GL_STATIC_DRAW);

	glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(6);
	glVertexAttribDivisor(6, 1);

	glVertexAttribPointer(7, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(0 + 4 * sizeof(GLfloat)));
	glEnableVertexAttribArray(7);
	glVertexAttribDivisor(7, 1);
	

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void MeshObject::DrawMesh()
{

	glBindVertexArray(VAO);
	if (instanced)
	{
		glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, size);
	}
	else
	{
		glDrawElements(GL_TRIANGLES, totalVertices, GL_UNSIGNED_INT, 0);
	}

}
void MeshObject::SetInstanceSize(int sX, int sY)
{
	size = sX * sY;
}
MeshObject::~MeshObject()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteBuffers(1, &MBO);
	glDeleteBuffers(1, &S3BO);
}

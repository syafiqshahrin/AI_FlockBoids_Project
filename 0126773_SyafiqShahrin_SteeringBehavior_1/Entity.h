#pragma once



class Entity
{
public:
	Entity();
	Entity(MeshObject* mesh, Shader* shader);
	Entity(MeshObject* mesh, Shader* shader, Entity* parent);
	void TranslateEntity(Vector3 newPosition);
	void RotateEntity(float angle, Vector3 axis);
	void ScaleEntity(Vector3 newScale);
	void DrawEntity(GLuint texture);
	void DrawEntityInstance(GLuint texture);
	void DrawEntity(GLuint texture, GLuint texture2); 
	void DrawEntity(GLuint texture, GLuint texture2, GLuint texture3);
	void SetShader(Shader* shader);
	void UseIdentityMatrix(bool identity);
	//
	Transform m_EntityTransform;
	MeshObject* m_EntityMesh;
	Shader* m_meshShader;
	Entity* Parent;
	bool useIdentity;
	Matrix4 gOthorMatrix;
	Matrix4 gViewMatrix;
	Matrix4 OrthoModelMatrix;
	Matrix4 modelMatrix;
};
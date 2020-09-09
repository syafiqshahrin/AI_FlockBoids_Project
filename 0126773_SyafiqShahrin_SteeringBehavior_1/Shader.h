#pragma once

#include<iostream>

class Shader
{
public:
	unsigned int ID;
	const char* vertexPath;
	const char* fragmentPath;
	Shader(const char* vertexPath, const char* fragmentPath);
	Shader();
	Shader(const Shader& old_obj);
	Shader& operator=(const Shader& old_obj);
	~Shader();
	void use();

	void setBool(const std::string &name, bool value) const;
	void setInt(const std::string &name, int value) const;
	void setFloat(const std::string &name, float value) const;
	void setVec3(const std::string &name, float x, float y, float z) const;
	void setVec4(const std::string &name, float x, float y, float z, float w) const;
	void setMat4(const std::string& name, const float* val) const;
private:
	void CompileShader();
};
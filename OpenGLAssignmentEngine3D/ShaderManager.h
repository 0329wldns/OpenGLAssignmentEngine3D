#pragma once
#include "pch.h"
#include "Singleton.h"
#include <unordered_map>

class ShaderManager : public Singleton<ShaderManager>
{
	friend class Singleton<ShaderManager>;

public:
	void init();

	void useProgram(const string& name);
	void setMat4(const string& name, const string& uniformName, const glm::mat4& mat);
	void setVec3(const string& name, const string& uniformName, const glm::vec3& vec);
	void setFloat(const string& name, const string& uniformName, float value);

private:
	ShaderManager() = default;
	~ShaderManager() = default;

	void loadShader(const string& name, const string& vertexPath, const string& fragmentPath);
	string readShaderFile(const string& filePath);
	uint32_t compileShader(uint32_t type, const string& source);

private:
	unordered_map<string, uint32_t> shaderMap{};
};
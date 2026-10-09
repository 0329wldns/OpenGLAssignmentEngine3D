#include "pch.h"
#include "ShaderManager.h"
#include <fstream>
#include <sstream>
#include <iostream>

void ShaderManager::init()
{
    // 기본 셰이더 로드
    loadShader("default", "default.vert", "default.frag");
}

void ShaderManager::useProgram(const std::string& name)
{
    if (shaderMap.find(name) != shaderMap.end())
    {
        glUseProgram(shaderMap[name]);
    }
}

void ShaderManager::setMat4(const std::string& name, const std::string& uniformName, const glm::mat4& mat)
{
    uint32_t program{ shaderMap[name] };
    int location{ glGetUniformLocation(program, uniformName.c_str()) };
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mat));
}

void ShaderManager::setVec3(const std::string& name, const std::string& uniformName, const glm::vec3& vec)
{
    uint32_t program{ shaderMap[name] };
    int location{ glGetUniformLocation(program, uniformName.c_str()) };
    glUniform3fv(location, 1, glm::value_ptr(vec));
}

void ShaderManager::setFloat(const std::string& name, const std::string& uniformName, float value)
{
    uint32_t program{ shaderMap[name] };
    int location{ glGetUniformLocation(program, uniformName.c_str()) };
    glUniform1f(location, value);
}

void ShaderManager::loadShader(const std::string& name, const std::string& vertexPath, const std::string& fragmentPath)
{
    std::string vertexCode{ readShaderFile(vertexPath) };
    std::string fragmentCode{ readShaderFile(fragmentPath) };

    uint32_t vertex{ compileShader(GL_VERTEX_SHADER, vertexCode) };
    uint32_t fragment{ compileShader(GL_FRAGMENT_SHADER, fragmentCode) };

    uint32_t program{ glCreateProgram() };
    glAttachShader(program, vertex);
    glAttachShader(program, fragment);
    glLinkProgram(program);

    int success{};
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetProgramInfoLog(program, 512, nullptr, infoLog);
        std::cerr << "셰이더 링킹 에러 (" << name << "): " << infoLog << '\n';
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);

    shaderMap[name] = program;
}

std::string ShaderManager::readShaderFile(const std::string& filePath)
{
    std::ifstream file;
    std::stringstream stream;
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try
    {
        file.open(filePath);
        stream << file.rdbuf();
        file.close();
    }
    catch (std::ifstream::failure& e)
    {
        std::cerr << "셰이더 파일 읽기 실패: " << filePath << '\n';
    }

    return stream.str();
}

uint32_t ShaderManager::compileShader(uint32_t type, const std::string& source)
{
    uint32_t shader{ glCreateShader(type) };
    const char* srcCode{ source.c_str() };
    glShaderSource(shader, 1, &srcCode, nullptr);
    glCompileShader(shader);

    int success{};
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cerr << "셰이더 컴파일 에러: " << infoLog << '\n';
    }

    return shader;
}
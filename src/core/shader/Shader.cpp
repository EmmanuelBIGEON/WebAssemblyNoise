#include "Shader.h"

#include <GLES3/gl3.h>
#include <Logger.h>
#include <fstream>
#include <sstream>

#include <glm/ext.hpp>

#include <WebData.h>

Shader* Shader::shader_default = nullptr;

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
    std::string vertexCode;
    std::string fragmentCode;

    std::ifstream vShaderFile(vertexPath);
    std::ifstream fShaderFile(fragmentPath); 

    std::stringstream vShaderStream, fShaderStream;

    vShaderStream << vShaderFile.rdbuf();
    fShaderStream << fShaderFile.rdbuf();

    vShaderFile.close();
    fShaderFile.close();

    vertexCode = vShaderStream.str();
    fragmentCode = fShaderStream.str();

    const char* vertexCodeStr = vertexCode.c_str();
    const char* fragmentCodeStr = fragmentCode.c_str();

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexCodeStr, NULL);
    glCompileShader(vertexShader);

    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        Logger::Log("ERROR::SHADER::VERTEX::COMPILATION_FAILED" + std::string(infoLog));
    }

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentCodeStr, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        Logger::Log("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED" + std::string(infoLog));
    }

    shaderID = glCreateProgram();
    glAttachShader(shaderID, vertexShader);
    glAttachShader(shaderID, fragmentShader);
    glLinkProgram(shaderID);

    glGetProgramiv(shaderID, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderID, 512, NULL, infoLog);
        Logger::Log("ERROR::SHADER::PROGRAM::LINKING_FAILED" + std::string(infoLog));
    }
    
    Logger::Log("Shader created.");

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

Shader::~Shader()
{
}

void Shader::Use()
{
    glUseProgram(shaderID);
}


void Shader::SetBool(const char* name, bool value) const
{
    glUniform1i(glGetUniformLocation(shaderID, name), (int)value);
}

void Shader::SetInt(const char* name, int value) const
{
    glUniform1i(glGetUniformLocation(shaderID, name), value);
}

void Shader::SetFloat(const char* name, float value) const
{
    glUniform1f(glGetUniformLocation(shaderID, name), value);
}

void Shader::SetVec2(const char* name, const glm::vec2& value) const
{
    glUniform2fv(glGetUniformLocation(shaderID, name), 1, glm::value_ptr(value));
}

void Shader::SetVec3(const char* name, const glm::vec3& value) const
{
    glUniform3fv(glGetUniformLocation(shaderID, name), 1, glm::value_ptr(value));
}

void Shader::SetVec4(const char* name, const glm::vec4& value) const
{
    glUniform4fv(glGetUniformLocation(shaderID, name), 1, glm::value_ptr(value));
}

void Shader::SetMat2(const char* name, const glm::mat2& value) const
{
    glUniformMatrix2fv(glGetUniformLocation(shaderID, name), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::SetMat3(const char* name, const glm::mat3& value) const
{
    glUniformMatrix3fv(glGetUniformLocation(shaderID, name), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::SetMat4(const char* name, const glm::mat4& value) const
{
    glUniformMatrix4fv(glGetUniformLocation(shaderID, name), 1, GL_FALSE, glm::value_ptr(value));
}


void Shader::InitShaders()
{
    shader_default = new Shader("shaders/default.vs", "shaders/default.fs");
}

Shader* Shader::GetShader(ShaderID shader)
{
    switch (shader)
    {
        case ShaderID_DEFAULT:
            return shader_default;
        default:
            throw new std::runtime_error("Couldn't find shader.");
            return nullptr;
    }
}

void Shader::UpdateResolution(const glm::vec2& resolution)
{
    if (shader_default != nullptr)
    {
        shader_default->Use();
        shader_default->SetVec2("resolution", resolution);
    }
}

void Shader::UpdateResolution(unsigned int width, unsigned int height)
{
    UpdateResolution(glm::vec2(width, height));
}

void Shader::UpdateTime(const float& time)
{
    if (shader_default != nullptr)
    {
        shader_default->Use();
        shader_default->SetFloat("time", time);
    }
}
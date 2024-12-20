#include "Shader.h"

#include <GLES3/gl3.h>
#include <Logger.h>
#include <fstream>
#include <sstream>

#include <glm/ext.hpp>
#include <nlohmann/json.hpp>

#include <WebData.h>

Shader* Shader::shader_default = nullptr;
Shader* Shader::shader_gabor = nullptr;
Shader* Shader::shader_gabor2 = nullptr;
Shader* Shader::shader_screen = nullptr;
glm::vec2 Shader::remembered_resolution = glm::vec2();
float Shader::remembered_time = 1.0f;

Shader::Shader(const char* vertexPath, const char* fragmentPath) : shaderName("Default")
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

    _vertexCode = vShaderStream.str();
    _fragmentCode = fShaderStream.str();

    const char* vertexCodeStr = _vertexCode.c_str();
    const char* fragmentCodeStr = _fragmentCode.c_str();

    _vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(_vertexShader, 1, &vertexCodeStr, NULL);
    glCompileShader(_vertexShader);

    int success;
    char infoLog[512];
    glGetShaderiv(_vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(_vertexShader, 512, NULL, infoLog);
        Logger::Log("ERROR::SHADER::VERTEX::COMPILATION_FAILED" + std::string(infoLog));
    }

    _fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(_fragmentShader, 1, &fragmentCodeStr, NULL);
    glCompileShader(_fragmentShader);

    glGetShaderiv(_fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(_fragmentShader, 512, NULL, infoLog);
        Logger::Log("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED" + std::string(infoLog));
    }

    shaderID = glCreateProgram();
    glAttachShader(shaderID, _vertexShader);
    glAttachShader(shaderID, _fragmentShader);
    glLinkProgram(shaderID);

    glGetProgramiv(shaderID, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderID, 512, NULL, infoLog);
        Logger::Log("ERROR::SHADER::PROGRAM::LINKING_FAILED" + std::string(infoLog));
    }
    
    Logger::Log("Shader created.");
}

Shader::~Shader()
{
}


std::string Shader::GetFragmentCode()
{
    return _fragmentCode;
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
    shader_screen = new Shader("shaders/screen.vs", "shaders/screen.fs");
    shader_screen->shaderName = "Screen";
    shader_screen->Use();
    shader_screen->SetInt("screenTexture", 0);

    shader_default = new Shader("shaders/default.vs", "shaders/default.fs");
    shader_default->shaderName = "Default";

    shader_gabor = new Shader("shaders/default.vs", "shaders/gabor.fs");
    shader_gabor->shaderName = "Gabor";

    shader_gabor2 = new Shader("shaders/default.vs", "shaders/gabor2.fs");
    shader_gabor2->shaderName = "Gabor2";
}

Shader* Shader::GetShader(ShaderID shader)
{
    switch (shader)
    {
        case ShaderID_DEFAULT:
            return shader_default;
        case ShaderID_GABOR:
            return shader_gabor;
        case ShaderID_GABOR2:
            return shader_gabor2;
        default:
            throw new std::runtime_error("Couldn't find shader.");
            return nullptr;
    }
}

Shader* Shader::GetScreenShader()
{
    return shader_screen;
}

std::string Shader::GetShadersListJSON()
{
    nlohmann::json json = {
        {
            {"name", shader_default->shaderName},
            {"id", ShaderID_DEFAULT}
        },
        {
            {"name", shader_gabor->shaderName},
            {"id", ShaderID_GABOR}
        },
        {
            {"name", shader_gabor2->shaderName},
            {"id", ShaderID_GABOR2}
        }
    };
    return json.dump();
}

void Shader::UpdateResolution(const glm::vec2& resolution)
{
    Shader::remembered_resolution = resolution;
    if (shader_default != nullptr)
    {
        shader_default->Use();
        shader_default->SetVec2("resolution", resolution);
    }
    if (shader_gabor != nullptr)
    {
        shader_gabor->Use();
        shader_gabor->SetVec2("resolution", resolution);
    }
    if (shader_gabor2 != nullptr)
    {
        shader_gabor2->Use();
        shader_gabor2->SetVec2("resolution", resolution);
    }
}

void Shader::UpdateResolution(unsigned int width, unsigned int height)
{
    UpdateResolution(glm::vec2(width, height));
}

void Shader::UpdateTime(const float& time)
{
    Shader::remembered_time = time;
    if (shader_default != nullptr)
    {
        shader_default->Use();
        shader_default->SetFloat("time", time);
    }
    if (shader_gabor != nullptr)
    {
        shader_gabor->Use();
        shader_gabor->SetFloat("time", time);
    }
    if (shader_gabor2 != nullptr)
    {
        shader_gabor2->Use();
        shader_gabor2->SetFloat("time", time);
    }
}

void Shader::UpdateFragmentShader(const std::string& fragmentCode)
{
    const char* fragmentCodeCstr = fragmentCode.c_str();
    unsigned int newFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(newFragmentShader, 1, &fragmentCodeCstr, NULL);
    glCompileShader(newFragmentShader);

    int success;
    char infoLog[512];
    glGetShaderiv(newFragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(newFragmentShader, 512, NULL, infoLog);
        Logger::Log("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED" + std::string(infoLog));
        return;
    }

    glDetachShader(shaderID, _fragmentShader);
    glAttachShader(shaderID, newFragmentShader);
    glLinkProgram(shaderID);

    // Check link status
    glGetProgramiv(shaderID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderID, 512, nullptr, infoLog);
        Logger::Log("ERROR::SHADER::PROGRAM::LINKING_FAILED" + std::string(infoLog));
        return;
    }

    // Update uniforms
    UpdateResolution(Shader::remembered_resolution);
    UpdateTime(Shader::remembered_time);

    glDeleteShader(_fragmentShader);
    _fragmentShader = newFragmentShader;
    _fragmentCode = fragmentCode;
}
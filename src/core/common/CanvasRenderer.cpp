#include "CanvasRenderer.h"

#include <GLES3/gl3.h>
#include <Logger.h>

float vertices[] = {
    -1.0f, -1.0f,
     1.0f, -1.0f,
    -1.0f,  1.0f,
     1.0f,  1.0f
};

CanvasRenderer::CanvasRenderer(const std::string& canvasID, ShaderID shaderID) : _canvasID(canvasID), _VAO(0), _VBO(0), _shaderID(shaderID)
{
}

CanvasRenderer::~CanvasRenderer()
{
}

void CanvasRenderer::SetShaderID(ShaderID shaderID)
{
    _shaderID = shaderID;
}

ShaderID CanvasRenderer::GetShaderID()
{
    return _shaderID;
}

bool CanvasRenderer::Init()
{
    glGenVertexArrays(1, &_VAO);
    glGenBuffers(1, &_VBO);

    glBindVertexArray(_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    return true;
}

void CanvasRenderer::Render()
{
    Shader::GetShader(_shaderID)->Use();
    glBindVertexArray(_VAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
}

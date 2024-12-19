#include "CanvasRenderer.h"

#include <GLES3/gl3.h>
#include <WebData.h>
#include <Logger.h>

float vertices[] = {
    -1.0f, -1.0f,
     1.0f, -1.0f,
    -1.0f,  1.0f,
     1.0f,  1.0f
};

float screenVertices[] = {
    // positions   // texCoords
    -1.0f,  1.0f,  0.0f, 1.0f,
    -1.0f, -1.0f,  0.0f, 0.0f,
    1.0f, -1.0f,  1.0f, 0.0f,
    -1.0f,  1.0f,  0.0f, 1.0f,
    1.0f, -1.0f,  1.0f, 0.0f,
    1.0f,  1.0f,  1.0f, 1.0f
};

CanvasRenderer::CanvasRenderer(const std::string& canvasID, ShaderID shaderID) : _canvasID(canvasID), _VAO(0), _VBO(0), _shaderID(shaderID)
{
    canvasWidth = WebData::GetCanvaWidth();
    canvasHeight = WebData::GetCanvaHeight();
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

    glGenVertexArrays(1, &_screenVAO);
    glGenBuffers(1, &_screenVBO);
    glBindVertexArray(_screenVAO);
    glBindBuffer(GL_ARRAY_BUFFER, _screenVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(screenVertices), &screenVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

    // Framebuffer RenderBuffer sampling.
    glGenFramebuffers(1, &FBORenderSampling);
    glBindFramebuffer(GL_FRAMEBUFFER, FBORenderSampling);
    glGenRenderbuffers(1, &RBOSampling);
    glBindRenderbuffer(GL_RENDERBUFFER, RBOSampling);
    glRenderbufferStorageMultisample(GL_RENDERBUFFER, 4, GL_RGB8, canvasWidth, canvasHeight);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, RBOSampling);

    //Framebuffer 1 sample texture.
    glGenFramebuffers(1, &FBOTexture);
    glBindFramebuffer(GL_FRAMEBUFFER, FBOTexture);
    glGenTextures(1, &colorTexture);
    glBindTexture(GL_TEXTURE_2D, colorTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, canvasWidth, canvasHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorTexture, 0);
    return true;
}

void CanvasRenderer::Render()
{
    glBindFramebuffer(GL_FRAMEBUFFER, FBORenderSampling);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    Shader::GetShader(_shaderID)->Use();
    glBindVertexArray(_VAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);

    glBindFramebuffer(GL_READ_FRAMEBUFFER, FBORenderSampling); // Set to read this time.
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, FBOTexture);
    glBlitFramebuffer(0, 0, canvasWidth, canvasHeight, 0, 0, canvasWidth, canvasHeight, GL_COLOR_BUFFER_BIT, GL_NEAREST);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    Shader::GetScreenShader()->Use();
    glBindVertexArray(_screenVAO);
    glBindTexture(GL_TEXTURE_2D, colorTexture);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

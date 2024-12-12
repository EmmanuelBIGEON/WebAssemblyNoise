#include "CanvasRenderer.h"

#include <GLES2/gl2.h>
#include <log.h>


float getElapsedTime() {
    static clock_t startTime = clock();
    return float(clock() - startTime) / CLOCKS_PER_SEC;
}

CanvasRenderer::CanvasRenderer(const std::string& canvasID) : _canvasID(canvasID)
{
}

CanvasRenderer::~CanvasRenderer()
{
}

void CanvasRenderer::Init()
{
    EMSCRIPTEN_WEBGL_CONTEXT_HANDLE emctx = emscripten_webgl_get_current_context();
    EmscriptenWebGLContextAttributes attr;
    emscripten_webgl_init_context_attributes(&attr);
    _contextWebGL = emscripten_webgl_create_context(_canvasID.c_str(), &attr);
}

void CanvasRenderer::Render()
{
    emscripten_webgl_make_context_current(_contextWebGL);
    float time = getElapsedTime();
    float value = (sin(time) + 1.0f) / 2.0f; 
    glClearColor(value, 1.0 - value, 1.0 - value, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
}

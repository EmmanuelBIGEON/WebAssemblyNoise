#include "Application.h"

#include <Shader.h>
#include <Logger.h>
#include <GLES3/gl3.h>

Application* Application::instance = nullptr;

Application::Application() : _canvasList({})
{
    _chrono.Start();
}

Application::~Application()
{
}

void Application::AddCanvas(std::shared_ptr<CanvasRenderer> ptr)
{
    _canvasList.push_back(ptr);
}

std::shared_ptr<CanvasRenderer> Application::AddCanvas(const std::string& canvasID)
{
    std::shared_ptr<CanvasRenderer> canvasRenderer = std::make_shared<CanvasRenderer>(canvasID);
    if(!canvasRenderer->Init()) return nullptr;
    _canvasList.push_back(canvasRenderer);
    return canvasRenderer;
}

void Application::RenderAll()
{
    // update uniform time.
    const auto& timeElapsed = _chrono.GetCurrentDuration();
    Shader::UpdateTime(timeElapsed); 

    glClear(GL_COLOR_BUFFER_BIT);
    for(const auto& canvas : _canvasList)
    {
        canvas->Render();
    }
}


std::shared_ptr<CanvasRenderer> Application::GetRenderer()
{
    if(_canvasList.empty()) return nullptr;
    return _canvasList.front();
}
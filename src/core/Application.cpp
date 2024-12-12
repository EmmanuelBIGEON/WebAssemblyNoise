#include "Application.h"

Application* Application::instance = nullptr;

Application::Application() : _canvasList({})
{
}

Application::~Application()
{
}

void Application::AddCanvas(std::shared_ptr<CanvasRenderer> ptr)
{
    _canvasList.push_back(ptr);
}

void Application::AddCanvas(const std::string& canvasID)
{
    std::shared_ptr<CanvasRenderer> canvasRenderer = std::make_shared<CanvasRenderer>(canvasID);
    if(!canvasRenderer->Init()) return;
    _canvasList.push_back(canvasRenderer);
}

void Application::RenderAll()
{
    for(const auto& canvas : _canvasList)
    {
        canvas->Render();
    }
}
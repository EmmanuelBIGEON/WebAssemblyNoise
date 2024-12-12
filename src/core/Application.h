#pragma once 

#include "CanvasRenderer.h"

#include <vector> 

class Application
{
    private:
        static Application* instance;
        Application();
    public: 
        static Application* GetApp() {
            if (!instance) instance = new Application(); 
            return instance;
        }
        virtual ~Application();

        void AddCanvas(std::shared_ptr<CanvasRenderer> ptr);
        void AddCanvas(const std::string& canvasID);

        void RenderAll();

    protected:
        std::vector<std::shared_ptr<CanvasRenderer>> _canvasList;
};
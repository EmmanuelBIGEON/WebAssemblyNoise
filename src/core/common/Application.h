#pragma once 

#include <CanvasRenderer.h>
#include <Chrono.h>

#include <vector> 
#include <memory>

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
        std::shared_ptr<CanvasRenderer> AddCanvas(const std::string& canvasID);

        void RenderAll();

        // A bit weird since i planned to use multiple canvas at the same time. Probably was a bad idea
        // to plan this far ahead as i don't think i ever will implement this feature
        // Anyway return the first canvasRenderer in the application list.
        std::shared_ptr<CanvasRenderer> GetRenderer();

    protected:
        std::vector<std::shared_ptr<CanvasRenderer>> _canvasList;

        Chrono _chrono;
};
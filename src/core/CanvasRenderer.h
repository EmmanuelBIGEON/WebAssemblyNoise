#pragma once 

#include <string>
#include <emscripten/html5.h>

class CanvasRenderer 
{
    public:
        CanvasRenderer(const std::string& canvasID);
        virtual ~CanvasRenderer();

        void Init();
        void Render();

    protected:
        std::string _canvasID;
        EMSCRIPTEN_WEBGL_CONTEXT_HANDLE _contextWebGL;
};
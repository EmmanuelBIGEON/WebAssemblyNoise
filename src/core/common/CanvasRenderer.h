#pragma once 

#include <string>
#include <emscripten/html5.h>

#include <Shader.h>

//! \class CanvasRenderer
//! \brief Render a canvas. Voluntarily simplified as we will only use a rectangle to render.
class CanvasRenderer 
{
    public:
        CanvasRenderer(const std::string& canvasID, ShaderID shaderID = ShaderID_DEFAULT);
        virtual ~CanvasRenderer();

        bool Init();
        void Render();

    protected:
        std::string _canvasID;
        ShaderID _shaderID;
        EMSCRIPTEN_WEBGL_CONTEXT_HANDLE _contextWebGL;
        unsigned int _VAO;
        unsigned int _VBO;
};
#pragma once 

#include <string>

#include <Shader.h>

//! \class CanvasRenderer
//! \brief Render a canvas. Voluntarily simplified as we will only use a rectangle to render.
class CanvasRenderer 
{
    public:
        CanvasRenderer(const std::string& canvasID, ShaderID shaderID = ShaderID_DEFAULT);
        virtual ~CanvasRenderer();

        void SetShaderID(ShaderID);
        ShaderID GetShaderID();

        bool Init();
        void Render();

    protected:
        std::string _canvasID;
        ShaderID _shaderID;
        unsigned int _VAO;
        unsigned int _VBO;
};
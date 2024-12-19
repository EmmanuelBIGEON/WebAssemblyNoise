#pragma once 

#include <string>
#include <vector>

#include <Shader.h>
#include <glm/ext.hpp>

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
        unsigned int _screenVAO;
        unsigned int _screenVBO;

        unsigned int canvasWidth;
        unsigned int canvasHeight;

        // WebGL2 doesn't support MSAA textures. 
        // Apparently it is because browsers doesn't render canvas this way
        // https://stackoverflow.com/questions/50613696/whats-the-purpose-of-multisample-renderbuffers
        unsigned int FBORenderSampling; 
        unsigned int RBOSampling;

        unsigned int FBOTexture;
        unsigned int colorTexture;
};
#pragma once 

#include <emscripten/bind.h>

namespace bindings
{
    //! \brief Return the list of available shaders. To be parsed.
    std::string GetShadersJSON();

    //! \brief Display the requested shaderid (from the enum)
    void DisplayShader(unsigned int shaderID);

    //! \brief Return current shader fragment code.
    std::string GetCurrentShaderCode();

    //! \brief Try to rebuild shader with input fragment code.
    void UpdateCurrentShaderCode(std::string fragmentCode);
}

// Connect functions to Module.
EMSCRIPTEN_BINDINGS(WANModule) {
    emscripten::function("GetShadersJSON", &bindings::GetShadersJSON);
    emscripten::function("DisplayShader", &bindings::DisplayShader);
    emscripten::function("GetCurrentShaderCode", &bindings::GetCurrentShaderCode);
    emscripten::function("UpdateCurrentShaderCode", &bindings::UpdateCurrentShaderCode);
}
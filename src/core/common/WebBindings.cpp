#include "WebBindings.h"

#include <string>

#include <Shader.h>
#include <Application.h>
#include <Logger.h>

namespace bindings
{
    std::string GetShadersJSON() {
        return Shader::GetShadersListJSON();
    }
    
    void DisplayShader(unsigned int shaderID)
    {
        Application::GetApp()->GetRenderer()->SetShaderID(static_cast<ShaderID>(shaderID));
    }

    std::string GetCurrentShaderCode()
    {
        const auto shaderID = Application::GetApp()->GetRenderer()->GetShaderID();
        return Shader::GetShader(static_cast<ShaderID>(shaderID))->GetFragmentCode();
    }

    void UpdateCurrentShaderCode(std::string fragmentCode)
    {
        const auto shaderID = Application::GetApp()->GetRenderer()->GetShaderID();
        Shader::GetShader(static_cast<ShaderID>(shaderID))->UpdateFragmentShader(fragmentCode);
    }
}
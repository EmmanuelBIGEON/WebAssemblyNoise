#pragma once

#include <glm/ext.hpp>

#include <string>

enum ShaderID
{
    ShaderID_DEFAULT = 1,
    ShaderID_GABOR
};

class Shader
{
    public:
        Shader(const char* vertexPath, const char* fragmentPath);
        virtual ~Shader();

        void Use();

        void SetBool(const char* name, bool value) const;
        void SetInt(const char* name, int value) const;
        void SetFloat(const char* name, float value) const;
        void SetVec2(const char* name, const glm::vec2& value) const;
        void SetVec3(const char* name, const glm::vec3& value) const;
        void SetVec4(const char* name, const glm::vec4& value) const;
        void SetMat2(const char* name, const glm::mat2& value) const;
        void SetMat3(const char* name, const glm::mat3& value) const;
        void SetMat4(const char* name, const glm::mat4& value) const;

        std::string shaderName;
        unsigned int shaderID; // Different than the enum ShaderID, this one comes from OpenGL

        void UpdateFragmentShader(const std::string& fragmentCode);
        std::string GetFragmentCode();

        static void InitShaders();
        static Shader* GetShader(ShaderID shader);
        static Shader* GetScreenShader();
        static std::string GetShadersListJSON(); // produce a JSON List of the available shaders 

        static void UpdateResolution(const glm::vec2& resolution);
        static void UpdateResolution(unsigned int width, unsigned int height);

        static void UpdateTime(const float& time);

    protected:
        static Shader* shader_default;
        static Shader* shader_gabor;


        static Shader* shader_screen;
        
        std::string _vertexCode;
        std::string _fragmentCode;
        unsigned int _vertexShader;
        unsigned int _fragmentShader;

        // Remembering uniforms for recompilation.
    private:
    
        static glm::vec2 remembered_resolution;
        static float remembered_time;
};
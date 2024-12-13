#include <Application.h>
#include <Shader.h>
#include <Directory.h>
#include <Logger.h>

#include <emscripten.h>
#include <iostream>
#include <GLES3/gl3.h>
#include <EGL/egl.h>

void initEGL();
void DumpGLInfo();

int main(int argc, char**argv)
{
    initEGL();
    // DumpGLInfo(); 

    Shader::InitShaders();

    Application* app = Application::GetApp();
    app->AddCanvas("#canvas");

    emscripten_set_main_loop([](){ Application::GetApp()->RenderAll(); }, 0, 1);
    return 0;
}

void initEGL()
{
    EM_ASM( Module.canvas = document.getElementById("canvas"); );

    EGLint attribute_list[] = {
    EGL_RED_SIZE, 8, EGL_GREEN_SIZE, 8, EGL_BLUE_SIZE, 8, 
    EGL_ALPHA_SIZE, 0, EGL_DEPTH_SIZE, 24, EGL_STENCIL_SIZE, 8, EGL_NONE};
    EGLConfig eglconfig = NULL;
    EGLint config_size,major,minor;
    EGLContext contextegl;
    EGLDisplay display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    eglInitialize(display,&major,&minor);

    if (eglChooseConfig (display, attribute_list, &eglconfig, 1, &config_size) == EGL_TRUE && eglconfig != NULL)
    {
        eglBindAPI(EGL_OPENGL_ES_API);
        EGLint anEglCtxAttribs[] = { EGL_CONTEXT_CLIENT_VERSION, 3, EGL_NONE, EGL_NONE }; 
        contextegl = eglCreateContext (display, eglconfig, EGL_NO_CONTEXT, anEglCtxAttribs);
    }

    eglMakeCurrent(display, EGL_NO_SURFACE, EGL_NO_SURFACE, contextegl);
}

void DumpGLInfo()
{
  // Informations générales OpenGL
  Logger::Log("GL_VERSION: " + std::string((const char*)glGetString(GL_VERSION)));
  Logger::Log("GL_VENDOR: " + std::string((const char*)glGetString(GL_VENDOR)));
  Logger::Log("GL_SHADING_LANGUAGE_VERSION: " + std::string((const char*)glGetString(GL_SHADING_LANGUAGE_VERSION)));
  int test = GL_SHADING_LANGUAGE_VERSION;

  // Informations EGL
  EGLDisplay display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
  Logger::Log("EGL_VERSION: " + std::string(eglQueryString((EGLDisplay )display, EGL_VERSION)));
  Logger::Log("EGL_VENDOR: " + std::string(eglQueryString((EGLDisplay )display, EGL_VENDOR)));
  Logger::Log("EGL_CLIENT_APIS: " + std::string(eglQueryString((EGLDisplay )display, EGL_CLIENT_APIS)));
}

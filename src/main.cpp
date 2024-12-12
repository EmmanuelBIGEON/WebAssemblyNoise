#include <emscripten/html5.h>

#include <Application.h>

int main(int argc, char**argv)
{
    Application* app = Application::GetApp();
    app->AddCanvas("#canvas");
    emscripten_set_main_loop([](){
        Application::GetApp()->RenderAll();
    }, 60, 1);
    return 0;
}
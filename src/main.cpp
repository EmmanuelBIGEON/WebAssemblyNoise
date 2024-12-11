#include "util/log.h"
#include <emscripten/html5.h>
#include <GLES2/gl2.h>
#include <emscripten.h>

float getElapsedTime() {
    static clock_t startTime = clock();
    return float(clock() - startTime) / CLOCKS_PER_SEC;
}

int main(int argc, char**argv)
{
    printjs("Creation du context webgl");
    EMSCRIPTEN_WEBGL_CONTEXT_HANDLE emctx = emscripten_webgl_get_current_context();
    EmscriptenWebGLContextAttributes attr;
    emscripten_webgl_init_context_attributes(&attr);
    EMSCRIPTEN_WEBGL_CONTEXT_HANDLE ctx = emscripten_webgl_create_context("#canvas", &attr);
    emscripten_webgl_make_context_current(ctx);

    printjs("Recouvrement de la zone de dessin en jaune");

    emscripten_set_main_loop([](){
        float time = getElapsedTime();
        float value = (sin(time) + 1.0f) / 2.0f; 
        glClearColor(value, 1.0 - value, 1.0 - value, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
    }, 60, 1);
    return 0;
}
#include "WebData.h"

#include <emscripten.h>

int WebData::GetCanvaWidth()
{
    return EM_ASM_INT({ return Module.canvas.width; });
}

int WebData::GetCanvaHeight()
{
    return EM_ASM_INT({ return Module.canvas.height; });
}


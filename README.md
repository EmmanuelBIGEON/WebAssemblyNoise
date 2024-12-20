# WebAssemblyNoise
A WebAssembly project about porting noise calculations C++ to a vue Application

![Preview](preview.png)

I use MingW through MSYS2, and you will need to install emscripten.
Emscripten allow you to transpile C++ code into Js. The whole WebAssembly thing.

- build.bat (build the WebAssembly module)
- start.bat (Install vue packages and start the frontend)

## Features

- List of default shaders available to browse 
- Editing shader code, allowing experimentation

I bind an uniform representing since the application started (in seconds) for dynamics.
I plan to have sliders to quickly witness different effects.
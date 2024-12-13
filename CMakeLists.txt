cmake_minimum_required(VERSION 3.20)

project(WebAssemblyNoise)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -l embind")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s FULL_ES3")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s MAX_WEBGL_VERSION=2")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --preload-file ../shaders/@/shaders") 
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s MODULARIZE=1") # using a function to create the module named "createParticleSandbox" (file : wasmloader.js )
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s EXPORT_NAME='createWebAssemblyNoiseModule'")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --extern-post-js ../src/wasmloader.js")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s EXPORTED_RUNTIME_METHODS=['ccall','cwrap','UTF8ToString','stringToUTF16']")

include_directories(
    ${PROJECT_INCLUDE_DIR}
    src/core/common
    src/core/shader
    src/util
)

set(SRCS 
    src/main.cpp

    src/util/Chrono.cpp
    src/util/Directory.cpp
    src/util/Generator.cpp
    src/util/Logger.cpp
    src/core/common/CanvasRenderer.cpp
    src/core/common/Application.cpp
    src/core/common/WebData.cpp
    src/core/common/WebBindings.cpp
    src/core/shader/Shader.cpp
)

add_executable(WebAssemblyNoise ${SRCS})

# The bin folder is a now a test folder for those who don't want to use Vue. You can simply http-server ./ it. 
install (TARGETS WebAssemblyNoise DESTINATION ${CMAKE_INSTALL_PREFIX})
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/WebAssemblyNoise.wasm DESTINATION ${CMAKE_INSTALL_PREFIX})
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/WebAssemblyNoise.data DESTINATION ${CMAKE_INSTALL_PREFIX})
install(FILES src/index.html DESTINATION ${CMAKE_INSTALL_PREFIX})
install(FILES src/favicon.ico DESTINATION ${CMAKE_INSTALL_PREFIX})

# Install in the vue public directory.
install (TARGETS WebAssemblyNoise DESTINATION ${PROJECT_FRONTEND_PUBLIC_DIR})
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/WebAssemblyNoise.wasm DESTINATION ${PROJECT_FRONTEND_PUBLIC_DIR})
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/WebAssemblyNoise.data DESTINATION ${PROJECT_FRONTEND_PUBLIC_DIR})
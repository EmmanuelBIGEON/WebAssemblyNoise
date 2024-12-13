@REM File: env_example.bat (to be copied to env.bat)
@REM This file is used by build.bat to set up the build environment.

set "MAIN_DIR=%cd%"

@REM Compilation settings
set PROJECT_NAME=WebAssemblyNoise
set PROJECT_BUILD_GENERATOR="MinGW Makefiles"
set PROJECT_BUILD_DIR=%MAIN_DIR%/build
set PROJECT_INCLUDE_DIR=%MAIN_DIR%/include
set PROJECT_DIR=%MAIN_DIR%
set TOOLCHAIN_FILE=C:/emscripten/emsdk/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake

@REM Install DIRs
set PROJECT_BIN_DIR=%MAIN_DIR%/bin
set PROJECT_FRONTEND_PUBLIC_DIR=%MAIN_DIR%/frontend/public
@REM @echo off

set CURRENT_DIR=%~dp0

@REM Check if config/env.bat exists
if not exist env.bat (
    echo env.bat not found.
    echo Please copy env_example.bat to env.bat and edit it.
    goto :EOF
)

@REM Load env.bat
call env.bat

echo [CMake] Generating project
cmake -S %PROJECT_DIR% -B %PROJECT_BUILD_DIR% -G %PROJECT_BUILD_GENERATOR% ^
-DCMAKE_TOOLCHAIN_FILE=%TOOLCHAIN_FILE% ^
-DPROJECT_INCLUDE_DIR=%PROJECT_INCLUDE_DIR% ^
-DPROJECT_FRONTEND_PUBLIC_DIR=%PROJECT_FRONTEND_PUBLIC_DIR% ^
-DCMAKE_INSTALL_PREFIX=%PROJECT_BIN_DIR%


cd %PROJECT_BUILD_DIR%
echo [CMake] Building project
cmake --build . -j 8
echo [CMake] Installing project
cmake --install .
cd %CURRENT_DIR%
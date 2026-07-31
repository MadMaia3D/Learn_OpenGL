@echo off

if not exist build (
    mkdir build
)

set GLFW_INCLUDE=-Idependencies/glfw/include
set GLFW_LIBRARY=-Ldependencies/glfw/lib/ -lglfw3 -lopengl32 -lgdi32 -luser32 -lshell32 -ladvapi32

set GLAD_INCLUDE=-Idependencies/glad/include
set GLAD_SOURCE=dependencies/glad/src/glad.c

set GLM_INCLUDE=-Idependencies/glm/include

set IMGUI_INCLUDE=-Idependencies/imgui/include

set MAIN_SOURCE=src/main.cpp

set INCLUDES=%GLFW_INCLUDE% %GLAD_INCLUDE% %GLM_INCLUDE% %IMGUI_INCLUDE%
set LIBRARIES=%GLFW_LIBRARY%
set SOURCES=%MAIN_SOURCE% %GLAD_SOURCE%
set OUTPUT=-o build/program.exe

g++ %SOURCES% %LIBRARIES% %INCLUDES% %OUTPUT%
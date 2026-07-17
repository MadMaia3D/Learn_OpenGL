@echo off

if not exist build (
    mkdir build
)

g++ src/main.cpp -o build/program.exe
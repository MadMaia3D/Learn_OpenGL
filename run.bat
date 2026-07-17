@echo off
if exist build\\program.exe (
    build\\program.exe
) else (
    echo ERROS: program executable not found in build\\program.exe
)
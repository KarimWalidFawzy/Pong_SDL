@echo off
cmake -S . -B build-windows -G "MinGW Makefiles"
if errorlevel 1 exit /b 1
cmake --build build-windows
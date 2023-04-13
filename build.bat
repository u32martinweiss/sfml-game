@echo off

REM
if not exist build mkdir build

REM
cd build

REM
cmake ..

REM
mingw32-make.exe

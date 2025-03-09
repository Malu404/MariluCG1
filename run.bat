echo off
g++ -O3 -march=native -I"E:\SDL2\include" I"E:\SDL2\include\SDL2" I"E:\SDL2\SDL2-2.30.9\include"  -D_REENTRANT -o cg1.exe main.cpp  -L"E:\SDL2\lib"  -lSDL2 -lSDL2_image -L "E:\SDL2\SDL2-2.30.9" -lSDL2  -mconsole
cg1.exe

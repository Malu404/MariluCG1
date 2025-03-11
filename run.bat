echo off
g++ -O3 -march=native -ISDL2/include -D_REENTRANT -o cg1.exe main.cpp  -LSDL2/lib -lSDL2 -lSDL2_image
cg1.exe

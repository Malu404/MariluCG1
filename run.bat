echo off
g++ -O3 -std=c++17 -march=native main.cpp -IC:/SDL2/include -LC:/SDL2/lib -lSDL2 -lmingw32 -lSDL2main -D_REENTRANT -o main.exe
main.exe

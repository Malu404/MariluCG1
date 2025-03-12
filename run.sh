#!/bin/bash
g++ -O3 -march=native -I/usr/include/SDL2 -D_GNU_SOURCE=1 -D_REENTRANT main.cpp -o cg1 -L/usr/lib -lSDL2 -lSDL2_image
./cg1
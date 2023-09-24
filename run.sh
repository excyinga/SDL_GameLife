#!/bin/bash

set -ex
gcc -o main.bin -lSDL2_ttf -lSDL2_image main.c `sdl2-config --cflags --libs`
./main.bin

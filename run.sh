#!/bin/bash

set -ex
gcc -masm=intel -o main.bin -I./include/ -lSDL2 -lSDL2_ttf -lSDL2_image -lSDL2_mixer ./src/*.c
./main.bin

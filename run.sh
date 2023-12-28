#!/bin/bash

set -ex
gcc -masm=intel -I./include/ -lSDL2 -lSDL2_ttf -lSDL2_image -lSDL2_mixer -o main.bin ./src/*.c
./main.bin

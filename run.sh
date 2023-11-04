#!/bin/bash

set -ex
gcc -o main.bin -I. -lSDL2 -lSDL2_ttf -lSDL2_image main.c window_components.c
./main.bin

#!/bin/bash
current_time=$(date "+%Y-%m-%d-%H:%M:%S")

x86_64-w64-mingw32-gcc ../main.c -o ./EstadoNovo/estadonovo.exe -L ../libs/win64/ -lraylib -lopengl32 -lgdi32 -lwinmm

./prepare-linux.sh

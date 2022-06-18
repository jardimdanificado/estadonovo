#!/bin/bash
current_time=$(date "+%Y-%m-%d-%H:%M:%S")

chmod +x ./Prepare-Linux.sh&&./Prepare-Linux.sh

x86_64-w64-mingw32-gcc ../main.c -o ./EstadoNovo/1964.exe -L ../libs/win64/ -lraylib -lopengl32 -lgdi32 -lwinmm

mkdir ./BUILD_WIN/1964/

robocopy ./data ./BUILD_WIN/ /s /e

gcc ../main.c -o ./BUILD_WIN/1964.exe -L ./raylib/win64 -lraylib -lopengl32 -lgdi32 -lwinmm

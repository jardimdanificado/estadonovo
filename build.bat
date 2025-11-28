mkdir ./BUILD_WIN/1964/

robocopy ./src ./BUILD_WIN/1964/ /s /e

gcc ./src/main.c -o ./BUILD_WIN/1964/1964.exe -L ./src/raylib_win -lraylib -lopengl32 -lgdi32 -lwinmm
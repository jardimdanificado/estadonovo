
#!/bin/bash
current_time=$(date "+%Y-%m-%d-%H:%M:%S")

rm -r ./EstadoNovo
mkdir ./EstadoNovo

gcc ../src/estadonovo.c -o ./EstadoNovo/estadonovo -lGL -L./libs/linux64/ -l:libraylib.a -lm -lpthread -ldl -lrt -lX11&&chmod +x ./EstadoNovo/estadonovo

cp -r ../src/data/ ./EstadoNovo/

cp ../credits.txt ./EstadoNovo/

mkdir ./EstadoNovo/src



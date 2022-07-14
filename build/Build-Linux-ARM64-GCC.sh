#!/bin/bash
current_time=$(date "+%Y-%m-%d-%H:%M:%S")

mkdir ../../BUILD/EstadoNovo_$current_time/

gcc ../src/main.c -o ../../BUILD/EstadoNovo_$current_time/estadonovo -lGL -L./libs/arm64/ -l:libraylib.a -lm -lpthread -ldl -lrt -lX11&&chmod +x ../../BUILD/EstadoNovo_$current_time/estadonovo

cp -r ../src/data/ ../../BUILD/EstadoNovo_$current_time/

cp ../credits.text ../../BUILD/EstadoNovo_$current_time/

cp ../src/config.text ../../BUILD/EstadoNovo_$current_time/

mkdir ../../BUILD/EstadoNovo_$current_time/src


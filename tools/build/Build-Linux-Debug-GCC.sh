
#!/bin/bash
current_time=$(date "+%Y-%m-%d-%H:%M:%S")

mkdir ../../../BUILD/EstadoNovo_$current_time/

gcc ../../main.c -o ../../../BUILD/EstadoNovo_$current_time/1964.AppImage -g -lGL -L../../libs/linux64 -l:libraylib.a -lm -lpthread -ldl -lrt -lX11&&chmod +x ../../../BUILD/EstadoNovo_$current_time/1964.AppImage

cp -r ../../data/ ../../../BUILD/EstadoNovo_$current_time/

cp ../../credits.text ../../../BUILD/EstadoNovo_$current_time/

cp ../../src/1964/config.text ../../../BUILD/EstadoNovo_$current_time/

cp ../../debug ../../../BUILD/EstadoNovo_$current_time/debug.AppImage&&cd ../../../BUILD/EstadoNovo_$current_time/&&./debug.AppImage



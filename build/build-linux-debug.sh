
#!/bin/bash
current_time=$(date "+%Y-%m-%d-%H:%M:%S")

mkdir ../../BUILD/EstadoNovo_$current_time/

gcc ../src/estadonovo.c -o ../../BUILD/EstadoNovo_$current_time/estadonovo -g -lGL -L./libs/linux64/ -l:libraylib.a -lm -lpthread -ldl -lrt -lX11&&chmod +x ../../BUILD/EstadoNovo_$current_time/estadonovo

cp -r ../src/data/ ../../BUILD/EstadoNovo_$current_time/

cp ../credits.txt ../../BUILD/EstadoNovo_$current_time/

cp ../debug ../../BUILD/EstadoNovo_$current_time/debug&&cd ../../BUILD/EstadoNovo_$current_time/&&./debug



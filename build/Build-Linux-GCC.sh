
#!/bin/bash
current_time=$(date "+%Y-%m-%d-%H:%M:%S")

mkdir ../../BUILD/EstadoNovo_$current_time/

gcc ../src/estadonovo.c -o ../../BUILD/EstadoNovo_$current_time/estadonovo -lGL -L./libs/linux64/ -l:libraylib.a -lm -lpthread -ldl -lrt -lX11&&chmod +x ../../BUILD/EstadoNovo_$current_time/estadonovo

cp -r ../src/data/ ../../BUILD/EstadoNovo_$current_time/

cp ../credits.text ../../BUILD/EstadoNovo_$current_time/

cp ../src/config.text ../../BUILD/EstadoNovo_$current_time/

mkdir ../../BUILD/EstadoNovo_$current_time/src

#7z a -t7z -m0=lzma2 -mx=9 -aoa -mfb=64 -md=32m -ms=on -mhe ../../BUILD/EstadoNovo_$current_time/src/src.7z ../



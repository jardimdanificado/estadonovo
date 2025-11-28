all:
	mkdir -p build
	cd libs && rm -rf urb && git clone https://github.com/jardimdanificado/urb
	
	gcc ./src/main.c -o ./build/estadonovo -I./libs/urb -lGL -L./libs/raylib -I./libs/raylib -l:libraylib.a -lm -lpthread -ldl -lrt -lX11

clean:
	rm -rf build/*
	libs/
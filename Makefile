all:
	mkdir -p build
	rm -rf build/*
	cp -r data build/data
	gcc ./src/main.c -o ./build/estadonovo -lGL -L./libs/raylib -l:libraylib.a -lm -lpthread -ldl -lrt -lX11
	chmod +x ./build/estadonovo
new:
	mkdir -p build
	cd libs
	git clone https://github.com/jardimdanificado/urb
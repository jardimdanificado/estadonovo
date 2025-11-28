all:
	mkdir -p build
	rm -rf build/*
	cp -r data build/data
	gcc ./src/main.c -o ./build/estadonovo -lGL -L./src/raylib -l:libraylib.a -lm -lpthread -ldl -lrt -lX11
	chmod +x ./build/estadonovo

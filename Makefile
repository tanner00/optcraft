.PHONY: build run clean

SRC = $(wildcard src/*.cpp src/*.c)

build:
	g++ $(SRC) -o optcraft -Iinclude -ldl `pkg-config glfw3 --cflags --libs`

run: build
	./optcraft

clean:
	rm optcraft
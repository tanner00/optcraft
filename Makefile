.PHONY: build run clean

SRC = $(wildcard src/*.cpp src/*.c)

build:
	g++ $(SRC) -o optcraft -std=c++17 -O2 -Wall -Wextra -Iinclude -ldl `pkg-config glfw3 --cflags --libs`

run: build
	./optcraft

clean:
	rm optcraft
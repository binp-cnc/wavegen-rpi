.phony: all

all: run

run: main.c
	gcc $^ -o $@ -lwiringPi

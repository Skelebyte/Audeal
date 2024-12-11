# TODO: add windows compilation
# TODO: add mac compilation??

compile:
	g++ example/main.cpp -lpthread -lm -ldl -o main

run: compile
	./main
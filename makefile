# TODO: add windows compilation
# TODO: add mac compilation??

compile_ex_simple:
	g++ example/simple.cpp -lpthread -lm -ldl -o build/examples/simple_example

run_simple: compile_ex_simple
	./build/examples/simple_example
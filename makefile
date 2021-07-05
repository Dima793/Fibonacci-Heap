all: dij_test

fib_test: fib_test.o
	g++ fib_test.o -o fib_test

fib_test.o: fib_test.cpp
	g++ -std=c++11 -c fib_test.cpp -o fib_test.o

dij_test: dij_test.o
	g++ dij_test.o -o dij_test

dij_test.o: dij_test.cpp
	g++ -std=c++11 -c dij_test.cpp -o dij_test.o

clean:
	rm *o

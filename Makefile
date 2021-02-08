all: test.cpp
	g++ -g --std=c++17 test.cpp -Ihash/ -Iiterator/
array: test.cpp
	g++ -g --std=c++17 test.cpp -Imy_array/
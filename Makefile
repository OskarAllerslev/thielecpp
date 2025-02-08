CXX = g++
CXXFLAGS = -I include -mconsole

all: main

main: main.cpp
	$(CXX) $(CXXFLAGS) main.cpp -o main

CXX = /usr/bin/g++
CXXFLAGS = -std=c++23 -I. -Wall

test: demo/test.cpp src/vec3.hpp
	$(CXX) $(CXXFLAGS) $< -o build/$@

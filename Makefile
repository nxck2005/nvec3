CXX = /usr/bin/g++
CXXFLAGS = -std=c++23 -I. -Wall
.PHONY: clean run test_vec3

test: demo/test.cpp src/vec3.hpp
	$(CXX) $(CXXFLAGS) $< -o build/$@

sphere: demo/sphere.cpp src/vec3.hpp
	$(CXX) $(CXXFLAGS) $< -o build/$@

test_vec3: tests/test_vec3.cpp src/vec3.hpp
	$(CXX) $(CXXFLAGS) $< -o build/$@

clean:
	rm -rf build/
	mkdir build/

run:
	build/sphere

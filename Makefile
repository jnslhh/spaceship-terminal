CXX = g++
CXXFLAGS = -O3 -Wall -Wextra -std=c++17
LDFLAGS = -lncursesw

spaceship: main.cpp
	$(CXX) $(CXXFLAGS) -o spaceship main.cpp $(LDFLAGS)

clean:
	rm -f spaceship
.PHONY: clean

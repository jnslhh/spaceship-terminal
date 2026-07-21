CXX = g++
CXXFLAGS = -O3 -Wall -Wextra -std=c++17

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
    LDFLAGS = -lncurses
else
    LDFLAGS = -lncursesw
endif

spaceship: main.cpp
	$(CXX) $(CXXFLAGS) -o spaceship main.cpp $(LDFLAGS)

clean:
	rm -f spaceship
.PHONY: clean

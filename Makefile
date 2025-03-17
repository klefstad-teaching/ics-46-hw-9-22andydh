CXXFLAGS=-ggdb -std=c++20 -Wall -Wextra -Werror -Wfatal-errors -pedantic

test:
	g++ $(CXXFLAGS) src/dijkstras_main.cpp src/dijkstras.cpp src/ladder.cpp -Isrc -o main.out
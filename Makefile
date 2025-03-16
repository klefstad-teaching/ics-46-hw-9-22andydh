CXXFLAGS=-ggdb -std=c++20 -Wall -Wextra -Werror -Wfatal-errors -pedantic

test:
	g++ $(CXXFLAGS) src/ladder_main.cpp src/ladder.cpp -Isrc -o main.out
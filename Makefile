CXXFLAGS = -std=c++1z -Wconversion -Wall -Werror # -Wextra -pedantic 

# target: dependencies
# 	action

all: driver.py solve
	python3 driver.py w
	./solve
	python3 driver.py r
# 	rm *.o solve *.txt

solve: main.o puzzle_state.o
	g++ $(CXXFLAGS) main.o puzzle_state.o -o solve

main.o: main.cpp
	g++ $(CXXFLAGS) -c main.cpp

puzzle_state.o: puzzle_state.cpp puzzle_state.h
	g++ $(CXXFLAGS) -c puzzle_state.cpp

clean:
	rm -f *.o solve *.txt

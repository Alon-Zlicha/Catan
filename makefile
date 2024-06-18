CXX = g++
CXXFLAGS = -std=c++11 -Werror -Wno-conversion
VALGRIND_FLAGS = -v --leak-check=full --show-leak-kinds=all --error-exitcode=99

SOURCES = board.cpp catan.cpp developmentCard.cpp edge.cpp hex.cpp knightCard.cpp monopolyCard.cpp piece.cpp player.cpp road.cpp roadsBuildingCard.cpp settlement.cpp vertex.cpp victoryPointCard.cpp yearOfPlentyCard.cpp
OBJECTS = $(SOURCES:.cpp=.o)
DEMO_OBJECTS = $(filter-out demo.o TestCounter.o, $(OBJECTS))  

.PHONY: all clean run tidy valgrind

all: demo test

run: demo
	./demo

demo: demo.o $(DEMO_OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o demo

test: TestCounter.o $(OBJECTS) test.o  
	$(CXX) $(CXXFLAGS) $^ -o test

tidy:
	clang-tidy $(SOURCES) -checks=bugprone-,clang-analyzer-,cppcoreguidelines-,performance-,portability-,readability-,-cppcoreguidelines-pro-bounds-pointer-arithmetic,-cppcoreguidelines-owning-memory --warnings-as-errors=-*

valgrind: test
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./test 2>&1 | { egrep "lost| at " || true; }

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o demo test


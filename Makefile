CXX := g++
CXXFLAGS := -std=c++17 -O2 -Wall -Wextra -Iinclude
LDFLAGS :=


SRC := src/main.cpp src/expression_parser.cpp
OBJ := $(SRC:.cpp=.o)
BIN := main


all: $(BIN)


$(BIN): $(OBJ)
	$(CXX) $(OBJ) -o $@ $(LDFLAGS)


src/%.o: src/%.cpp include/expression_parser.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(BIN)
	./$(BIN)

clean:
	rm -f $(OBJ) $(BIN)


.PHONY: all clean
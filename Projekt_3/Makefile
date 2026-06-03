CXX      = g++
CXXFLAGS = -O2 -std=c++20 -Wall -Wextra -I.

SRC  = main.cpp
BIN  = app.exe

all: $(BIN)

$(BIN): $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $^

run: $(BIN)
	./$(BIN)

clean:
	rm -f $(BIN) out.txt out_cxx20.txt

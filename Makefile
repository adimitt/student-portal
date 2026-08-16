CXX      := g++
CXXFLAGS := -std=c++17 -Wall -Wextra
SRC      := $(wildcard src/*.cpp)
BIN      := bin/portal

all: release

release: CXXFLAGS += -O2
release: $(BIN)

debug: CXXFLAGS += -g -O0 -DDEBUG
debug: $(BIN)

$(BIN): $(SRC)
	@mkdir -p bin
	$(CXX) $(CXXFLAGS) $(SRC) -o $@

run: release
	./$(BIN)

clean:
	rm -rf bin

.PHONY: all release debug run clean

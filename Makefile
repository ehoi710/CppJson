.PHONY: clean

INCLUDE = include
SOURCE = source

LIB = lib
BIN = bin

CPPFILES = $(wildcard $(SOURCE)/*.cpp)
CPPOBJFILES = $(patsubst $(SOURCE)/%.cpp, $(BIN)/%.o, $(CPPFILES))
REMOVE = rm -rf

lib/libcppjson.a: $(CPPOBJFILES)
	@echo "=== build main ==="
	ar rc $@ $^
	@echo "=== build main complete ==="

bin/%.o: source/%.cpp
	g++ -c $< -Iinclude -o $@

clean:
	@echo "=== clean ==="

	$(REMOVE) $(LIB)/*
	$(REMOVE) $(BIN)/*

	@echo "=== clean complete ==="

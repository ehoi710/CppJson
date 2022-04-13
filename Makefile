<<<<<<< HEAD
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
=======
CPPFILES = $(wildcard source/*.cpp)
CPPOBJS = $(patsubst source/%.cpp, bin/%.o, $(CPPFILES))

lib/libcppjson.a: $(CPPOBJS) 
	@echo "=== build library ==="
	ar rc $@ $^
#	g++ -o main -Iinclude $^
	@echo "=== build complete ==="

bin/%.o: source/%.cpp
	g++ -c -o $@ -Iinclude $<

clean:
ifeq ($(OS), Windows_NT)
	del /q bin
	del /q lib
else
	rm -rf bin/*
	rm -rf lib/*
endif
>>>>>>> develop

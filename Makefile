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
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
	rm -rf bin/*
	rm -rf lib/*

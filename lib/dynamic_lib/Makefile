libmymath.so:add.o sub.o
	g++ -shared -o $@ $^

add.o:add.cpp
	g++ -fPIC -c add.cpp

sub.o:sub.cpp
	g++ -fPIC -c sub.cpp

.PHONY:output
output:
	mkdir -p mylib/include
	mkdir -p mylib/lib
	cp ./*.hpp mylib/include
	cp ./*.a mylib/lib	

.PHONY:pack
pack:
	tar -czf mylib.tar.gz ./mylib

.PHONY:unpack
unpack:
	tar -xzf mylib.tar.gz

.PHONY:clean
clean:
	rm -rf libmymath.so
	rm -rf ./*.o
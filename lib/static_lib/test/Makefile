libmymath.a:add.o sub.o
	ar -rc $@ $^
add.o:add.cpp
	g++ -c add.cpp
sub.o:sub.cpp
	g++ -c sub.cpp

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
	rm ./*.o
	rm -rf libmymath.a
	rm -rf mylib
	rm -rf mylib.tar.gz
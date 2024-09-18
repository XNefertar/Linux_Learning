.PHONY:all
all:mysignal mykill

mykill:mykill.cc
	g++ -std=c++11 -o $@ $^

mysignal:mysignal.cc
	g++ -std=c++11 -o $@ $^

.PHONY:clean
clean:
	rm -rf mykill mysignal
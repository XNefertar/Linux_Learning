.PHONY:all
all:mysignal alarm

mysignal:mysignal.cc
	g++ -std=c++11 -o $@ $^

alarm:alarm.cc
	g++ -std=c++11 -o $@ $^

.PHONY:clean
clean:
	rm -rf mysignal alarm
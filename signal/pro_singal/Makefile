.PHONY:all
all:mysignal alarm signal hardware_signal

mysignal:mysignal.cc
	g++ -std=c++11 -o $@ $^

alarm:alarm.cc
	g++ -std=c++11 -o $@ $^

signal:signal.cc
	g++ -std=c++11 -o $@ $^

hardware_signal:hardware_signal.cc
	g++ -std=c++11 -o $@ $^

.PHONY:clean
clean:
	rm -rf mysignal alarm signal hardware_signal
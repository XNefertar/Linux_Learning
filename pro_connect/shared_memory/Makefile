.PHONY:all
all:server client

server:server.cc
	g++ -std=c++11 -o $@ $^
client:client.cc
	g++ -std=c++11 -o $@ $^

.PHONY:clean
clean:
	rm -rf server client named_pipe
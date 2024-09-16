.PHONY:all
all:_server _client

_server:server.cc
	g++ -std=c++11 -o $@ $^ -g

_client:client.cc
	g++ -std=c++11 -o $@ $^ -g

.PHONY:clean
clean:
	rm -rf _server _client TEST
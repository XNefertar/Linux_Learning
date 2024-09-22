.PHONY:all
all:pthread_ctrl thread_ctrl_adv

pthread_ctrl:pthread_ctrl.cc
	g++ -std=c++11 -o $@ $^ -lpthread


thread_ctrl_adv:thread_ctrl_adv.cc
	g++ -std=c++11 -o $@ $^ -lpthread

.PHONY:clean
clean:
	rm -rf pthread_ctrl thread_ctrl_adv
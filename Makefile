.PHONY: all

all: 
	rm -f backend.out	
	gcc main_backend.c client_for_msg_queue.c client_for_frontend.c -o backend.out

run:
	./backend.out
 

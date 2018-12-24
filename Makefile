all:	a4chat

a4chat: chat.o socket.o enc.o a4-util.o
	gcc -o a4chat chat.o socket.o enc.o a4-util.o

chat.o: chat.c
	gcc -c chat.c

socket.o: socket.c
	gcc -c socket.c

enc.o: enc.c
	gcc -c enc.c

clean:
	rm *.o a4chat

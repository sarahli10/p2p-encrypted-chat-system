# p2p-encrypted-chat-system
A peer-to-peer encrypted chat system that communicates over TCP/IP sockets.

Source Files:
- chat.c, basis of the chat system
- enc.c, used for encyrpting messages
- socket.c, the sockets used for communicating

Compilation Command:
- make

Launching Instructions:
1. In one terminal window, change the directory to where the files are located, type "make" and hit the Enter key to create the executable called "a4chat"
2. Type "./a4chat" in the same window and hit Enter to run the program
3. Open another terminal window and change the directory just like before, type "./a4chat 127.0.0.1" and hit Enter to run the program

Operating Instructions:
1. The two users will take turns sending messages, the user who entered the IP address will go first.
2. Follow the prompts and enter a message, after you're done, hit Enter to send it.
3. Talk to each other! (or yourself...)
4. Enter "quit" to stop the program.

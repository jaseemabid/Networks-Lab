# A simple chat server with unix sockets.

Author : Jaseem Abid <jaseemabid@gmail.com>
License : GPL V3

### Testing instructions

1. compile the server code `gcc server.c -o server -pthread`
2. compile the client code `gcc client.c -o client -pthread`
3. Run server `./server <port number>`. Eg: `./server 8089`
4. Run the client in a different terminal. `./client <server> <port>`. Eg: `./client localhost 8089`
5. Run any number of clients in different terminals
6. Send messages to user<n> in the format `<userid> <Message>`. Eg: `1 hello world`

Code tested on an ubuntu 10.04 LTS machine with gcc (Ubuntu 4.4.3-4ubuntu5) 4.4.3

### Usage

A message can be sent from peer to peer in the format '@<peer id> Message'
It is assumed now that the entered peed id is valid integer. A '*' will enable users to broadcast message to all logged in users at the same given time.
Sample message `@3 Hello world :)`
Clients use a multi threaded approach to recieve and send messages the same time. A thread runs listening to the socket and one to stdin. This enables concurrent chat between multiple users.

### References

* Original source of the demo codes : http://www.linuxhowtos.org/C_C++/socket.htm
* Threading tutorial : https://computing.llnl.gov/tutorials/pthreads/
* A good place to start learning git would be https://gist.github.com/1210107

### Questions?

If you have any questions, please feel free to ask me at <jaseemabid@gmail.com>

### Report bugs at [github](/jaseemabid/Networks-Lab/issues)

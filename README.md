# Networks lab programming codes by Jaseem Abid

### Testing instructions

1. compile the server code `gcc server.c -o server -pthread`
2. compile the client code `gcc client.c -o client -pthread`
3. Run server `./server <port number>`. Eg: `./server 8089`
4. Run the client in a different terminal. `./client <server> <port>`. Eg: `./client localhost 8089`
5. Run any number of clients in different terminals
6. Send messages to user<n> in the format `<userid> <Message>`. Eg: `1 hello world`

## Report bugs at [github](https://github.com/jaseemabid/Networks-Lab/issues)

### References

* Original source of the demo codes : http://www.linuxhowtos.org/C_C++/socket.htm
* Threading tutorial : https://computing.llnl.gov/tutorials/pthreads/

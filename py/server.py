#!/usr/bin/python
import socket

'''
Rapando C Samson - P15/1568/2015
CSC315 Distributed Systems Assignment
Server and Client (Python2.7)

Server Side Code

The server creates the socket, then listens on the network, waiting for the clients to connect
When a client connects, it prints out the client address and the port they communicate through
It also prints the data recieved from the client on screen then sends the same data back to the client
It the continues to listen for any other request
'''

# create a TCP/IP socket

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Bind the socket to the port
host = '127.0.0.1'
port = int(raw_input("Enter the port : "))
# create a tuple to hold the host and the port
server_address = (host, port)
print "starting up on {}".format(str(server_address))
sock.bind(server_address)

# listen puts the socket in server mode and accept puts it in listen mode

sock.listen(1)
while True:
    #wait for the connection
    print "waiting for connection"
    connection, client_address = sock.accept()

    #data is transmitted by sendall and received by recv

    try:
        print "connection from {}".format(str(client_address))
        #receive data - maximum of 1024 bytes, print it on the screen, change it to upper case and send it to the client

        data = connection.recv(1024)
        print "received  - {}".format(str(data))
        if data:
            print "sending data back to client"
            connection.sendall(data.upper())
        else:
            print "no more data from {}".format(client_address)
            connection.close()


    finally:
        connection.close()

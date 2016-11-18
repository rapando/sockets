#!/usr/bin/python

'''
Rapando C Samson - P15/1568/2015
CSC315 Distributed Systems Assignment
Server and Client (Python2.7)

Client Side Code

It connects to a server with the specified address and port
It then sends the user input to the server and prints out any response it gets
'''
import socket

#create the TCP/IP socket
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

#connect the socket to the port where the server is listening, ask the user to input the ap address

host = raw_input("Enter the IP address : ")
port = int(raw_input("Enter the port : "))
#create a tuple to hold the hostname and th port
server_address = (host, port)
print "connecting to {} on port {}".format(host, port)
sock.connect(server_address)
# we send data with sendall and recieve with recv

try:
    #send data
    data = raw_input("Enter data to send: ")
    print "sending >> {} ...".format(data)
    sock.sendall(data)

    rec = sock.recv(1024)
    print "recieved << {}\n".format(rec)
    sock.close()
except:
    print "could not open the connection"
    sock.close()

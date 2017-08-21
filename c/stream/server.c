#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>

#include "../methods.h"

int main (int argc, char *argv[]) {

    struct matrixStructure ms;
    int socket_desc, client_sock, c, read_size,  i, j;
    long int det;
    struct sockaddr_in server, client;
    char client_message[2000];

	if (argc < 2 || argc > 2){
		puts ("--- You have to pass the port number as input, eg ./server 8080 ---");
		puts ("--- Exiting ---");
		return 0;
	}

    puts ( "\n" );
    puts ( "--- Rapando C Samson ---" );
    puts ( "--- P15/1568/2015    ---" );

    printLine ();

    /*
        Create the socket, exit if unsuccessful
    */
    socket_desc = socket ( AF_INET, SOCK_STREAM, 0 );
    if ( socket_desc < 0) {
        printf ( "--- Unable to create socket ---\n" );
        return 1;
    }
    else {
        puts ( "Socket Created" );
        printLine ();

        /*
            Define the socket family, address and port
        */
        server.sin_family = AF_INET;
        server.sin_addr.s_addr = INADDR_ANY;
        server.sin_port = htons(atoi(argv[1]));

        /*
            Bind the socket, exit if unsuccessful
        */
        if ( bind (socket_desc, ( struct sockaddr *) &server, sizeof ( server) ) < 0 ) {
            puts ( "--- Binding Failed ---\n" );
            return 1;
        }
        puts ( "Binding Finished");

        /*
            Listen for client connections
        */
        listen ( socket_desc, 3);

        puts ( "Waiting for connections from clients " );


        /*
            Accept conneciton from client,
        */
		while ( 1 ) {
			c = sizeof ( struct sockaddr_in );
			client_sock = accept ( socket_desc, ( struct sockaddr *) &client, ( socklen_t * ) &c );
	        if (client_sock < 0) {
	            puts ( "-- Accept failed ---" );
	            continue;
	        }
	        puts ("\n--- Connection Accepted from a Client ---\n");
			/*
	            Receive the matrix information from the client and assign it to ms
	        */
	         read_size = recv ( client_sock , &ms, sizeof(struct matrixStructure), 0 );
	         printLine();
	         /*
	            Print out the matrix sent by the client
	         */
	         puts("the matrix received");
	            for (i=0; i < ms.size; i++) {
	                for (j = 0; j < ms.size; j++) {
	                    printf("%d ", ms.matrix[i][j]);
	                }
	                printf ("\n");
	            }
	            /*
	                Get the determinant of the matrix and send it to the client
	            */
	            det = getDeterminant( ms.matrix, ms.size );
	            printf ("the determinant is %ld\n",det);
	            sprintf(client_message,"%ld", det);
	            write ( client_sock, client_message, strlen(client_message));
		}
    }
    printLine();
	printf("\n");
    return 0;
}

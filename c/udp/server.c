#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "../methods.h"

int main ( int argc, char const *argv[] ) {
	int sock, client_sock, c, i,j;
	struct sockaddr_in server, from;
	char buf[1024];
	struct matrixStructure matrix = {};
  long int  determinant;

	if ( argc < 2 || argc > 2 ){
		puts ( "--- You have to pass the port number as input, eg ./server 8080 ---" );
		puts ( "--- Exiting ---" );
		return 0;
	}


	puts ( "\n" );
    puts ( "--- Rapando C Samson ---" );
    puts ( "--- P15/1568/2015    ---" );

    printLine ();

	/*
		Create the socket, exit if unsuccessful
	*/
	sock = socket ( AF_INET, SOCK_DGRAM , 0 );
	if ( sock < 0 ) {
		puts ( "--- Error creating socket ---" );
		return 1;
	}
	else {
		printf ( "Socket created. Running on port :%d\n", atoi ( argv[1] ) );
		printLine();

		/*
		Define the socket family, port and address
		*/
		bzero ( &server, sizeof ( server ) ); // clearing the server
		server.sin_family = server.sin_family = AF_INET;
        server.sin_addr.s_addr = INADDR_ANY;
        server.sin_port = htons ( atoi ( argv[1] ) );
	}

	/* Bind the server , exit if unsuccessful*/
	if ( bind ( sock, ( struct sockaddr * ) &server, sizeof ( server ) ) < 0 ) {
		puts ( "--- Unable to bind the server to the socket ---" );
		return 1;
	}

	/*
	Run the server, waiting for client messages
	*/
	c = sizeof ( struct sockaddr_in );

	while( 1 ) {
		client_sock = recvfrom ( sock, &matrix, sizeof ( struct matrixStructure ) , 0, ( struct sockaddr * ) &from, &c );
		if ( client_sock < 0 ) {
			puts ( "--- Error on recvfrom ---" );
			printLine();
			continue;
		}
		// get the determinant
		puts ( "Received matrix" );
        for ( i = 0; i < matrix.size; i++ ) {
            for ( j = 0; j <matrix.size; j++ ) {
             printf ( "%d ", matrix.matrix[i][j] );
            }
            printf ( "\n" );
        }

        determinant = getDeterminant( matrix.matrix, matrix.size );
        puts ( "Sending the determinant of the matrix to the client" );

		client_sock = sendto ( sock, &determinant, sizeof ( determinant ), 0,  ( struct sockaddr  * ) &from, c );
		if ( client_sock < 0 ) {
			puts ( "--- Error on sendto ---" );
			continue;
		}
        printLine();
	}
	printLine();
	printf( "\n" );
	return 0;
}

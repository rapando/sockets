#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "../methods.h"

int main ( int argc, char *argv[] ) {

    struct matrixStructure ms = {};
    int i, j, n, sock, x;
    struct sockaddr_in server, from;
	  struct hostent *hp;
    char  buffer[2000], *buf;
	  int length;
    long int determinant;

	if ( argc < 2 ) {
		puts ( "--- You have to pass the port number as input, eg ./client 8080 ---" );
		puts ( "--- Exiting ---" );
		return 0;
	}


    puts ( "\n" );
    puts ( "--- Rapando C Samson ---" );
    puts ( "--- P15/1568/2015    ---" );

    printLine ();
    puts ( "\n" );

    /*
        create the socket , exit if unsuccessful
    */
    sock = socket ( AF_INET, SOCK_DGRAM, 0 );
    if ( sock < 0 ) {
        puts ( "--- Unable to create the socket ---\n" );
        return 1;
    }

    else {
        /*
            Define the socket family, address and port
        */
        server.sin_family = AF_INET;
		hp = gethostbyname ( "localhost" );

		if ( hp == 0 ) {
			puts ("--- Unknown Host ---");
			return 1;
		}
		bcopy ( ( char * ) hp -> h_addr, ( char * ) &server.sin_addr, hp->h_length );
		server.sin_port = htons (atoi (argv[1]));
		length = sizeof ( struct sockaddr_in );

		/*
			Read the size of the matrix from the user n where 2 <= n <= 10
			Any other value prompts a re-entry
		*/

		puts ( "\nEnter matrix size n " );
		n = getInt( 2, 2, 10 );

		/*
			Enter the positive integer values of the matrix
		*/
		puts ( "\nEnter the values of the matrix " );
		for ( i = 0; i < n; i++ ) {
		    for ( j = 0; j < n; j++ ) {
                printf ( "Pos [%d][%d] , ", i, j );
                ms.matrix[i][j] = getInt( 4, -100, 100 );
		    }
		    printf ( "\n" );
		}

		printf ( "\nThe %d by %d matrix set successfully\n", n, n );

		ms.size = n;



		x = sendto ( sock, &ms, sizeof ( struct matrixStructure ), 0, ( struct sockaddr * ) &server, length );
		if ( x < 0 ) {
			puts ( "--- Error on sendto ---" );
			return 1;
		}
		x = recvfrom ( sock, &determinant, sizeof ( determinant ), 0, ( struct sockaddr * ) &from, &length);
		if ( x < 0 ) {
			puts ( "--- Error on recvfrom ---" );
			return 1;
		}

		printf ( "The determinant is %ld\n", determinant );
	}
    printLine ();
	printf ( "\n" );
    return 0;
}

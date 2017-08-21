#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>

#include "../methods.h"

int main ( int argc, char *argv[] ) {

    struct matrixStructure ms = {};
    int i, j, n, sock;
    struct sockaddr_in server;
    char  server_reply[2000];

	if (argc < 2){
		puts ("--- You have to pass the port number as input, eg ./client 8080 ---");
		puts ("--- Exiting ---");
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
    sock = socket ( AF_INET, SOCK_STREAM, 0 );
    if ( sock < 0 ) {
        puts ( "--- Unable to create the socket ---\n" );
        return 1;
    }

    else {
        /*
            Define the socket family, address and port
        */
        server.sin_family = AF_INET;
        server.sin_port = htons( atoi ( argv[1] ) );
        server.sin_addr.s_addr = INADDR_ANY;

        /*
            Connect to the server, exit if unsuccessful
        */
        if ( connect ( sock, ( struct sockaddr * )  &server, sizeof ( server ) ) < 0 ) {
            puts ( "--- Connection Failed ---\n--- Exiting ---\n" );
            printLine ();
            return 1;
        }

        puts ( "--- Connection established ---\n" );
        printLine ();

        /*
            Read the size of the matrix from the user n where 2 <= n <= 10
            Any other value prompts a re-entry
        */
		puts ( "\nEnter matrix size n " );
		n = getInt(2, 2, 10);


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

        /*
            Open the communication with the server
        */

        while ( 1 ) {
            /*
                Send the matrix information to the server
            */
            if ( send ( sock, &ms, sizeof ( struct matrixStructure ), 0 ) < 0 ) {
                puts ( "--- Sending Failed ---" );
                return 1;
            }
            puts ( "sent successfully" );

            /*
                Print the reply from the server
            */
            if ( recv ( sock, server_reply, 2000, 0 ) < 0 ) {
                puts ( "--- Receiving failed ---" );
            }
            printf ( "Determinant : %s\n", server_reply );
             /*
                Break from the loop
            */
            break;
        } // end while
    }
    printLine();
	printf("\n");
    return 0;
}

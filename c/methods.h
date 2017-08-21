/*
Define the matrix structure
*/

struct matrixStructure {
    int size;
    int matrix[20][20];
} ;

/*
    Verify the validity of the port
*/
int verifyPortInput ( char *port ) {
    int p = atoi(port);
    if (p < 8000 || p > 10000) {
      return 0;
    }
    else {
      return 1;
    }
}

/*
    print a separator
*/
void printLine () {
    puts ( "------------------------------------" );
}

/*
get the determinant of the n by n matrix
*/
/*
long int getDeterminant( int matrix[20][20], int order ) {
	int pr, c[20], tempMatrix[20][20], j , p , q , t;
  long int determinant;
  if ( order == 2 ) {
  	determinant = 0;
    determinant = ( matrix[1][1] * matrix[2][2] ) - ( matrix[1][2] * matrix[2][1] );
    return determinant;
  }

  else {
    for ( j = 1; j <= order; j++ ) {
    	int r = 1,s = 1;
    	for ( p = 1; p <= order; p++ ) {
    		for ( q = 1; q <= order; q++ ) {
    			if ( p != 1 && q != j ) {
    				tempMatrix[r][s] = matrix[p][q];
    				s++;
    				if ( s > order - 1 ) {
    					r++;
    					s = 1;
    				}
    			}
    		}
    	}
    	for ( t = 1 , pr = 1; t <= ( 1 + j ); t++ )
    	pr = ( -1 ) * pr;
    	c[j] = pr * getDeterminant ( tempMatrix , order - 1 );
    }
    for ( j = 1, determinant = 0; j <= order; j++ ) {
    	determinant = determinant + ( matrix[1][j] * c[j] );
    }
    return determinant;
   }
}
*/
long int getDeterminant ( int mat[20][20], int order ) {
    struct matrixStructure matrix;
    matrix.matrix = mat;
    matrix.size = order;
    long int determinant, r;
    int i, j, k;

    if ( matrix.size == 2 ) {
        determinant = ( matrix.matrix[0][0] * matrix.matrix[1][1] ) - ( matrix.matrix[0][1] * matrix.matrix[1][0] );
        return determinant;
    }

    else {
        for ( i = 0; i < matrix.size; i++ ) {
            for ( j = 0; j < matrix.size; j++ ) {
                if (i > j) {
                    r = matrix.matrix[i][j] / matrix.matrix[j][j];
                    for ( k=0; k<matrix.size;k++ ) {
                        matrix.matrix[i][k] = r * matrix.matrix[j][k];
                    }
                }
            }
        }

        determinant = 1;

        // multiplying the main diagnol
        for ( i = 0; i < matrix.size; i++ )  {
            determinant *= matrix.matrix[i][i];
        }

        return determinant;
    }
}
*/

/*
Validate the input to be an integer value
*/
int getInt ( int length, int min, int max ) {
	int num = 0;
	char inputChars [64];

	while ( num == 0 ) {
		printf ( "Enter values ( %d <= n <= %d ) : ", min, max );
		fgets ( inputChars, 63, stdin );

		if ( strlen( inputChars ) <= 0 || strlen ( inputChars ) > length ) {
			printf ( "--- Input is of invalid length ---\n" );
			continue;
		}
		if ( sscanf ( inputChars, "%d", &num ) != 1 ) {
			printf ( "--- Invalid input ---\n" );
			num = 0;
			continue;
		}

		if ( num < min || num > max ) {
			printf ( "--- Input out of range ---\n" );
			num = 0;
			continue;
		}

		else {
			break;
		}
	}
	return num;
}

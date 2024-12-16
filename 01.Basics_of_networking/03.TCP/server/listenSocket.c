#include "network.h"


void listenSocket( SOCKET *sock ) {

	printf("Trying listening..\n");
	if ( listen( *sock, 10 )) {
	
		fprintf( stderr, "\tFailed.\n");
		exit( GETSOCKETERRNO() );
	} else {
	
		printf( "\tListening.\n" );
	}
}

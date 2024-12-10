#include "network.h"


void bindSocket( struct addrinfo **address, SOCKET *sock ) {

	printf("Binding socket to local address...\n");
	if ( bind( *sock, (*address)->ai_addr, (*address)->ai_addrlen) ) {

		fprintf( stderr, "\tFailed.\n");
		CLOSESOCKET( *sock );
		exit( GETSOCKETERRNO() );
	} else {
	
		printf( "\tBinded.\n" );
		freeaddrinfo( *address );
	}
}

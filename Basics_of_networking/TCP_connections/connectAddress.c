#include "network.h"


int connectAddress( struct addrinfo **address , SOCKET *socketpeer) {

	printf("Connecting..\n");

	if ( connect( *socketpeer, (*address)->ai_addr , (*address)->ai_addrlen )) {
	
		fprintf(stderr, "Connection failed.\n");
		exit(GETSOCKETERRNO());
	}
	freeaddrinfo(*address);

	printf("Connected.\n");
}

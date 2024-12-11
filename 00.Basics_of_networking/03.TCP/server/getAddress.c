#include "network.h"


void getAddress(struct addrinfo **address) {

	char host[100], serv[100];
	struct addrinfo hints;
	memset( &hints, 0, sizeof(hints) );
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	printf("Configuring local address...\n");
	if ( getaddrinfo( 0, "8080", &hints, address) ) {
	
		fprintf( stderr, "\tFailed.\n");
		exit(GETSOCKETERRNO());
	}

	printf("\tConfigured: ");
	getnameinfo( (*address)->ai_addr, (*address)->ai_addrlen,
			host, sizeof(host),
			serv, sizeof(serv),
			NI_NUMERICHOST);
	printf( "%s : %s\n", host, serv );
}

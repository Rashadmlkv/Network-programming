#include "network.h"


int getAddress( int argc , char *argv[] , struct addrinfo **address) {

	if ( argc != 3 ) {
	
		fprintf( stderr , "Usage: <address> <port>\n");
		exit(0);
	}

	printf( "Configuring remote address..\n" );
	
	struct addrinfo hints;
	memset( &hints , 0 , sizeof(hints) );
	hints.ai_socktype = SOCK_STREAM; 
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	
	if ( getaddrinfo(argv[1], argv[2] , &hints , address ) ) {
	
		fprintf( stderr , "Couldn't configure remote address.\n");
		exit(GETSOCKETERRNO());
	}

	printf("Configured remote address:\n\n");

	char addressBuffer[100];
	char serviceBuffer[100];
	getnameinfo( (*address)->ai_addr , (*address)->ai_addrlen,
		       	addressBuffer, sizeof(addressBuffer),
			serviceBuffer, sizeof(serviceBuffer),
			NI_NUMERICHOST);
	printf( "%s : %s\n\n", addressBuffer, serviceBuffer );
}

#include "networkV2.h"


void createSocket( sock *address ) {

	#if defined (_WIN32)
	WSADATA d;
	if ( WSAStartup( MAKEWORD( 2 , 2 ), &d ) ) {
	
		fprintf( stderr, "Failed to initialize\n");
		exit(GETSOCKETERRNO());
	}
	#endif //_WIN32
	
	
	struct addrinfo hints;
	memset(	&hints, 0, sizeof(hints) );
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_flags = AI_PASSIVE;
	getaddrinfo( "127.0.0.1", "8080", &hints, &(*address).addr );


	printf("Creating socket..\n");
	(*address)._socket = socket( (*address).addr->ai_family, 
				(*address).addr->ai_socktype, 
				(*address).addr->ai_protocol);

	if ( !ISVALIDSOCKET( (*address)._socket) ) {
	
		fprintf( stderr, "socket() failed\n");
		exit(GETSOCKETERRNO());
	} else {
		printf( "Created\n" );
	}



	printf("Binding socket to local address...\n");
	if ( bind((*address)._socket,
		 (*address).addr->ai_addr, 
		 (*address).addr->ai_addrlen) ) {
	
		fprintf( stderr, "bind() failed\n");
		CLOSESOCKET( (*address)._socket);
		exit( GETSOCKETERRNO() );
	} else {
		freeaddrinfo( (*address).addr );
		printf("Binded\n"); 
	}
}

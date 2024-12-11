#include "network.h"


void createSocket(struct addrinfo **address, SOCKET *sock) {

	#if defined (_WIN32)
	WSADATA d;
	WSAStartup(MAKEWORD(2,2), &d);
	#endif	

	printf( "Creating socket...\n" );
	*sock = socket( (*address)->ai_family,
		       	(*address)->ai_socktype, 
			(*address)->ai_protocol);
	
	if ( !ISVALIDSOCKET(*sock) ) {

		fprintf( stderr, "\tFailed.\n" );
		exit(GETSOCKETERRNO());
	} else {
	
		printf( "\tCreated.\n" );
	}
}

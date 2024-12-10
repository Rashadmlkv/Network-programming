#include "network.h"


int createSocket(struct addrinfo **address , SOCKET *socketpeer) {

	#if defined (_WIN32)
	WSADATA d;
	if ( WSAStartup( MARKDOWN(2,2) , &d) ) {

		fprintf(stderr, "Couldn't initialize socket.\n");
		exit(GETSOCKETERRNO());
	}
	#endif	//WIN32
	
	printf("Creating socket..\n");

	*socketpeer = socket((*address)->ai_family, (*address)->ai_socktype, (*address)->ai_protocol);

	if ( !ISVALIDSOCKET(socketpeer) ) {
	
		fprintf( stderr ,"Couldn't create socket.\n");
		exit(GETSOCKETERRNO());
	}

	printf("Socket created.\n");
}

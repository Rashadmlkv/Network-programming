#include "networkV2-1.h"


void createSocket () {

	//Initialize windows sockets
	#if defined (_WIN32)
	WSADATA d;
	if (WSAStartup (MAKEWORD(2,2), &d)) {

		fprintf (stderr, "Initialize failed\n");
		exit (GETSOCKETERRNO());
	}
	#endif
	
	struct addrinfo hints;
	memset (&hints, 0, sizeof(hints));
	hints.ai_socktype = SOCK_DGRAM;

	//Get address of remote server
	if (getaddrinfo ("127.0.0.1", "8080", &hints, &address.addr)) {
	
		fprintf (stderr, "getarrdinfo() failed\n");
		exit (GETSOCKETERRNO());
	}

	//Print address of remote server
	char addr[100], serv[100];
	getnameinfo (address.addr->ai_addr,
			address.addr->ai_addrlen,
			addr, sizeof(addr),
			serv, sizeof(serv),
			NI_NUMERICHOST | NI_NUMERICSERV);
	printf("Remote address:\t%s : %s\n", addr, serv);

	//Create socket
	address._socket = socket (address.addr->ai_family,
				address.addr->ai_socktype,
				address.addr->ai_protocol);
	if ( !ISVALIDSOCKET (address._socket)) {
	
		fprintf (stderr, "socket() failed\n");
		exit (GETSOCKETERRNO());
	}
}

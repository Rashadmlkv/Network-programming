#include "networkV3.h"


void create_socket(const char* host, const char *port) {

	//windows setup
	#ifdef _WIN32
		WSAData d;
		if (WSAStartup (MAKEWORD (2,2), &d)) {
	
			fprintf (stderr, "Initialization failed.\n");
			exit (1);
		}
	#endif

	//configure server endpoint
	printf ("Configuring local address..\n");

	struct addrinfo hints;
	memset (&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	getaddrinfo (host, port, &hints, &addresss.addr);

	//create socket
	addresss._socket = socket (addresss.addr->ai_family,
					addresss.addr->ai_socktype,
					addresss.addr->ai_protocol);

	if ( !ISVALIDSOCKET(addresss._socket)) {
	
		fprintf (stderr, "socket() failed.\n");
		exit (1);
	}
	
	//bind socket to address
	if (bind (addresss._socket, addresss.addr->ai_addr, addresss.addr->ai_addrlen)) {
	
		fprintf (stderr, "bind() failed.\n");
		CLOSESOCKET (addresss._socket);
		exit (1);
	}
	freeaddrinfo (addresss.addr);

	//listen on connections
	printf ("Listening..\n");

	if (listen (addresss._socket, 10) < 0) {
	
		fprintf (stderr, "listen() failed");
		CLOSESOCKET(addresss._socket);
		exit (1);
	}
}

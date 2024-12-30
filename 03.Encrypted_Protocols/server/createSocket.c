#include "secnetwork.h"


void createSocket () {

	//windows socket initialization
	#ifdef _WIN32
		WSADATA d;
		if (WSAStartup (MAKEWORD (2,2), &d)) {
	
			fprintf (stderr, "Initialization failed\n");
			exit (1);
		}
	#endif

	//address configuration
	printf ("Configuring address\n");
	struct addrinfo hints;
	memset (&hints, 0, sizeof (hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;
	getaddrinfo (0, "8080", &hints, &address.addr);

	//socket creation
	printf ("Creating socket\n");
	address._socket = socket (address.addr->ai_family,
					address.addr->ai_socktype,
					address.addr->ai_protocol);
	if (!ISVALIDSOCKET (address._socket)) {
	
		fprintf (stderr, "socket() failed\n");
		exit (1);
	}

	//socket configuration
	printf ("Binding socket");
	if (bind (address._socket,
				address.addr->ai_addr,
				address.addr->ai_addrlen)) {
	
		fprintf (stderr, "bind() failed\n");
		CLOSESOCKET (address._socket);
		exit (1);
	}
	freeaddrinfo (address.addr);

	printf ("Listening\n");
	if (listen (address._socket, 10) < 0) {
	
		fprintf (stderr, "listen() failed\n");
		CLOSESOCKET (address._socket);
		exit (1);
	}
}

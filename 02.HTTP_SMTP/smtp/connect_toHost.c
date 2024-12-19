#include "smtp.h"


void connect_to_host (const char* host, const char* port) {


	#if defined(_WIN32)
		WSADATA d;
		if (WSAStartup(MAKEWORD(2, 2), &d)) {
		fprintf(stderr, "Failed to initialize.\n");
		return 1;
		}
	#endif

	//get address
	printf ("Configuring remote address..\n");
	struct addrinfo hints;
	memset (&hints, 0, sizeof(hints));
	hints.ai_socktype = SOCK_STREAM;

	if (getaddrinfo (host, port, &hints, &address.addr)) {
	
		fprintf (stderr, "getaddrinfo() failed\n");
		exit (1);
	}

	printf ("Remote address:\n");
	char buffhost[100], buffserv[100];
	getnameinfo(address.addr->ai_addr,
			address.addr->ai_addrlen,
			buffhost, sizeof(buffhost),
			buffserv, sizeof(buffserv),
			NI_NUMERICHOST);
	printf ("%s : %s", buffhost, buffserv);


	//create socket
	address._socket = socket (address.addr->ai_family,
					address.addr->ai_socktype,
					address.addr->ai_protocol);
	if (!ISVALIDSOCKET (address._socket)) {
	
		fprintf (stderr, "socket() failed\n");
		exit (1);
	}


	//connect to address
	if (connect (address._socket,
				address.addr->ai_addr,
				address.addr->ai_addrlen)) {
	
		fprintf (stderr, "connect() failed\n");
		CLOSESOCKET (address._socket);
		exit (1);
	}
	freeaddrinfo (address.addr);
	printf ("Connected\n");
}

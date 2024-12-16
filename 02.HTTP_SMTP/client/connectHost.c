#include "networkV2-1.h"


void connect_to_host(char *hostname, char *port) {


	#if defined(_WIN32)
		WSADATA d;
		if (WSAStartup(MAKEWORD(2, 2), &d)) {
		fprintf(stderr, "Failed to initialize.\n");
		return 1;
		}
	#endif

	//get Destination address
	printf ("Configuring remote address..\n");
	struct addrinfo hints;
	memset (&hints, 0, sizeof(hints));
	hints.ai_socktype = SOCK_STREAM;

	if (getaddrinfo (hostname, port, &hints, &address.addr)) {
	
		fprintf (stderr, "getaddrinfo() failed.\n");
		exit (1);
	}

	printf ("Remote address: \n");

	char addr[100], serv[100];

	getnameinfo(address.addr->ai_addr, address.addr->ai_addrlen,
			addr, sizeof(addr),
			serv, sizeof(serv),
			NI_NUMERICHOST);
	printf ("%s : %s\n", addr, serv);


	//create Socket
	printf ("Creating socket..\n");
	
	address._socket = socket (address.addr->ai_family,
					address.addr->ai_socktype,
					address.addr->ai_protocol);

	if ( !ISVALIDSOCKET(address._socket) ) {
	
		fprintf (stderr , "socket() failed.\n");
		exit (1);
	}

	//connect to Server
	printf ("Connecting..\n");

	if (connect (address._socket, 
				address.addr->ai_addr,
				address.addr->ai_addrlen)) {
	
		fprintf (stderr, "connect() failed.\n");
		exit (1);
	}
	freeaddrinfo(address.addr);
	printf ("Connected.\n");
}

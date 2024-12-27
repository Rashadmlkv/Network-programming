#include "secnetwork.h"


void createSocket (char *hostname, char *port) {

	#ifdef _WIN32
		WSADATA d;
		if (WSAStartup (MARKDOWN (2,2), &d)) {
	
			fprintf ("Inistialization failed\n");
			exit (1);
		}
	#endif

	//get address and print
	printf ("Configuring remote address\n");
	struct addrinfo hints;
	memset (&hints, 0, sizeof (hints));
	hints.ai_socktype = SOCK_STREAM;

	if (getaddrinfo (hostname, port, &hints, &address.addr)) {
	
		fprintf (stderr, "getaddrinfo() failed\n");
		exit (1);
	}

	printf ("Configured remote address\n");
	char host[100], serv[100];
	getnameinfo (address.addr->ai_addr,
			address.addr->ai_addrlen,
			host, sizeof (host),
			serv, sizeof (serv),
			NI_NUMERICHOST);
	printf ("%s : %s\n", host, serv);


	//create socket
	printf ("Creating socket\n");
	address._socket = socket (address.addr->ai_family,
		       			address.addr->ai_socktype,
				       	address.addr->ai_protocol);
	if (!ISVALIDSOCKET (address._socket)) {
	
		fprintf (stderr, "socket() failed\n");
		exit (1);
	}

	//connect
	printf ("Connecting to %s\n", host);
	if (connect (address._socket,
				address.addr->ai_addr, address.addr->ai_addrlen)) {
	
		fprintf (stderr, "connect() failed\n");
		CLOSESOCKET (address._socket);
		exit (1);
	}
	freeaddrinfo(address.addr);
	printf ("Connected\n");
}

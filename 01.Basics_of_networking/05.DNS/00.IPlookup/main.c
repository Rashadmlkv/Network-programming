#include "networkV2-1.h"

#if defined (_WIN32)
#define AI_ALL 0x0100
#endif

sock address;

int main ( int argc , char *argv[] ) {

	if (argc != 2) {
	
		fprintf (stderr, "Usage: <example.com>\n");
		exit(0);
	}

	#ifdef _WIN32
	WSADATA d;
	if (WSAStartup (Makeword (2,2), &d)) {

		fprintf (stderr , "Initialization failed\n");
		exit (0);
	}
	#endif
	
	struct addrinfo hints;
	memset (&hints, 0, sizeof(hints));
	hints.ai_flags = AI_ALL;
	
	printf("Resolving hostname '%s'\n", argv[1]);
	if (getaddrinfo (argv[1], "https", &hints, &address.addr)) {
	
		fprintf (stderr, "Couldn't find ip address\n");
		exit (0);	
	}

	char addrbuff[100], servbuff[100];
	struct addrinfo *addres = address.addr;
	do {

		getnameinfo (addres->ai_addr,
				addres->ai_addrlen,
				addrbuff, sizeof(addrbuff),
				servbuff, sizeof(servbuff),
				NI_NUMERICHOST | NI_NUMERICSERV);
		printf("%s : %s\n", addrbuff, servbuff);	
	} while ((addres = addres->ai_next));

	freeaddrinfo (address.addr);

	#ifdef _WIN32
	WSACleanup();
	#endif
}

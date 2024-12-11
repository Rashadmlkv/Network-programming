#include "networkV2.h"


void createSocket( sock *address );
void closeSocket( sock *address );


int main (void) {

	sock address;
	struct sockaddr_storage clientAddress;
	socklen_t clientLen = sizeof( clientAddress );
	char read[1024], addrbuff[100], servbuff[100];


	createSocket( &address );
	int received = recvfrom(address._socket,
		       	read,
		       	sizeof(read),
		       	0,
		       	(struct sockaddr*)&clientAddress,
		       	&clientLen);
	printf("Received %d:\n%.*s\n", received, received, read);

	printf("From:\n");
	getnameinfo( (struct sockaddr*) &clientAddress,
			clientLen,
			addrbuff, sizeof(addrbuff),
			servbuff, sizeof(servbuff),
			NI_NUMERICHOST | NI_NUMERICSERV );
	printf("%s : %s\n", addrbuff, servbuff);

	closeSocket( &address );
	return 0;
}

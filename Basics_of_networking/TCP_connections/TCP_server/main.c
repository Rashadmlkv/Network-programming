#include "network.h"


void getAddress( struct addrinfo **address );
void createSocket( struct addrinfo **address, SOCKET *sock );
void bindSocket( struct addrinfo **address, SOCKET *sock );
void listenSocket( SOCKET *sock );
int mainLoop( SOCKET *sock );
void closeSocket( SOCKET *sock );


int main (void) {

	struct addrinfo *address;
	SOCKET sock;

	getAddress( &address );
	createSocket( &address, &sock );
	bindSocket( &address, &sock );
	listenSocket( &sock );
	mainLoop( &sock );
	closeSocket( &sock );
	return 0;
}

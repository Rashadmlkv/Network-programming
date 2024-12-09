#include "network.h"


int main ( int argc , char *argv[] ) {

	struct addrinfo *address;
	SOCKET socketpeer;
	
	getAddress( argc , argv , &address );
	createSocket( &address , &socketpeer);
	connectAddress( &address, &socketpeer);
	programLoop( &socketpeer);
	closeSocket( &socketpeer);
	return 0;
}

#include "network.h"


void closeSocket(SOCKET *socketpeer) {

	printf( "Closing socket..\n");
	CLOSESOCKET(*socketpeer);

	#if defined (_WIN32)
		WSACleanup();
	#endif
	printf("Finished.\n");
}

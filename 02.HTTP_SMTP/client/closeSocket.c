#include "networkV2-1.h"


void closeSocket() {

	printf ("Closing socket..\n");
	
	CLOSESOCKET(address._socket);
	
	#ifdef _WIN32
	WSACleanup();
	#endif

	printf ("Closed.\n");
}

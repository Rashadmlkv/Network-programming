#include  "network.h"


void closeSocket( SOCKET *sock ) {

	CLOSESOCKET(*sock);

	#if defined (_WIN32)
	WSACleanup();
 	#endif
}

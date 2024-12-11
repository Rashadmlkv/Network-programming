#include "networkV2.h"


void closeSocket ( sock address ) {

	CLOSESOCKET( address._socket);

	#if defined (_WIN32)
	WSACleanup();
	#endif
}

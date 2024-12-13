#include "networkV2-1.h"


void closeSocket() {

	CLOSESOCKET (address._socket);

	#if defined (_WIN32)
	WSACleanup();
	#endif
}

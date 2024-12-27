#include "secnetwork.h"


void closeSocket (SSL_CTX ctx, SSL ssl) {

	printf ("Closing socket\n");
	SSL_shutdown (ssl);
	CLOSESOCKET (address._socket);
	SSL_free (ssl);
	SSL_CTX_free (ctx);

	#ifdef _WIN32
		WSACleanup();
	#endif

	printf ("Finished\n");
}

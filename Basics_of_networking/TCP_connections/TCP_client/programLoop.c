#include "network.h"


void programLoop( SOCKET *socketpeer ){

	printf("To send data, enter text followed by enter.\n");

	while(1) {
	
		fd_set reads;
		FD_ZERO(&reads);
		FD_SET( *socketpeer , &reads);

		#if !defined (_WIN32)
		FD_SET( 0, &reads);
		#endif

		struct timeval timeout;
		timeout.tv_sec = 0;
		timeout.tv_usec = 10000;

		if ( select( *socketpeer + 1, &reads, 0,0, &timeout ) < 0 ) {
		
			fprintf(stderr, "select() failed.\n");
			break;
		}

		if (FD_ISSET(*socketpeer, &reads)) {
		
			char read[4096];
			int bytesReceived = recv(*socketpeer, read , 4096 , 0);
			if (bytesReceived < 1) {
			
				printf("Connection closed by peer.\n");
				break;
			}
			printf("Received (%d bytes): %.*s", bytesReceived, bytesReceived, read);
		}

		#if defined (_WIN32)
			if (_kbhit()) {
		#else
			if (FD_ISSET(0, &reads)) {
		#endif
				char read[4096];
				if ( !fgets(read, 4096, stdin) ) break;
				printf( "Sending: %s", read );
				int bytesSent = send( *socketpeer , read , strlen(read) , 0 );
				printf("Sent %d bytes.\n" , bytesSent);
			}
		}
}

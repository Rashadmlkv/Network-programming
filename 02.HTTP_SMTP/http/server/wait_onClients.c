#include "networkV3.h"


fd_set wait_on_clients() {

    printf ("Waiting on clients\n");
	fd_set reads;
	FD_ZERO (&reads);
	FD_SET	(addresss._socket, &reads);
	SOCKET max_socket = addresss._socket;
	
    struct client_info *ci = clients;
    while(ci) {
        FD_SET(ci->socket, &reads);
        if (ci->socket > max_socket)
        max_socket = ci->socket;
        ci = ci->next;
    }
	if ( select (max_socket + 1, &reads, 0,0,0) < 0) {
	    
		fprintf (stderr, "select() failed.\n");
		CLOSESOCKET (addresss._socket);
		exit (1);
	}
	return reads;
}

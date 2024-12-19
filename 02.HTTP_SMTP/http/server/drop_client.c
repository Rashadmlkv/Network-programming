#include "networkV3.h"


void drop_client(struct client_info *client) {

    printf ("dropping client");
	CLOSESOCKET(client->socket);

	struct client_info **p = &clients;

	while (*p) {
	
		if (*p == client) {
		
			*p = client->next;
			free(client);
			return;
		}

		p = &(*p)->next;
	}

	fprintf (stderr, "drop_client not found.\n");
	exit (1);
}

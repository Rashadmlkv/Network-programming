#include "networkV3.h"


struct client_info *get_client(SOCKET s) {

    printf ("Getting client\n");
	struct client_info *ci = clients;

	//search client
	while (ci) {
	
		if (ci->socket == s) {
		
			break;
		}
		ci = ci->next;
	}

	if (ci) return ci;

	//create new one if not found
	struct client_info *n = (struct client_info*) calloc (1, sizeof(struct client_info));

	if (!n) {
	
		fprintf (stderr, "Out of memory.\n");
		exit (1);
	}

	n->address_length = sizeof(n->address);
	n->next = clients;
	clients = n;
	return n;
}

#include "networkV3.h"


sock addresss;
struct client_info *clients;
int main (void) {

	create_socket(0, "8080");
	
	while (1) {
	
		fd_set reads;

        //accept client
		reads = wait_on_clients();        
		if (FD_ISSET (addresss._socket, &reads)) {
		
			struct client_info *client = get_client(-1);

			client->socket = accept (addresss._socket, 
						(struct sockaddr *)&(client->address),
						&(client->address_length));
			if ( !ISVALIDSOCKET (client->socket)) {
			
				fprintf (stderr, "accpet() failed.\n");
				return 1;
			}
			printf ("New connection from %s.\n", get_client_address(client));
		}




        //handle request
		struct client_info *client = clients;
		while (client) {

			struct client_info *next = client->next;

			if (FD_ISSET(client->socket, &reads)) {

				if (MAX_REQUEST_SIZE == client->received) {
				
					send_400 (client);
					continue;
				}
				int r = recv (client->socket,
						client->request + client->received,
						MAX_REQUEST_SIZE - client->received, 0);

				if (r < 1) {
				
					printf ("Unexpected disconnect from %s.\n", get_client_address(client));
					drop_client(client);
				} else {
					client->received += r;
					client->request[client->received] = 0;

					char *q = strstr (client->request, "\r\n\r\n");

					if (q) {

						if (strncmp("GET /", client->request, 5)) {
						
							send_400(client);
						} else {
						
							char *path = client->request + 4;
							char *end_path = strstr (path ," ");

							if (!end_path) {
							
								send_400 (client);
							} else {
							
								*end_path = 0;
								serve_resource (client, path);
							}
						}
					} //if (q)
				}
			} //FD_ISSET
			client = next;
		} //while (client)
	}	//while
	
	printf ("\nClosing socket\n");
	CLOSESOCKET (addresss._socket);

	#ifdef _WIN32
		WSACleanup();
	#endif
	
	printf ("finished\n");
	return 0;
}

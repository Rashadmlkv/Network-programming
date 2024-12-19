#include "networkV3.h"


void send_400(struct client_info *client) {

	const char *c400 = "HTTP/1.1 400 Bad Request\r\n"
				"Connection: close\r\n"
				"Content-Length: 11\r\n\r\nBad Request";
printf ("sending 404\n");
	send (client->socket, c400, strlen(c400), 0);
	drop_client (client);
}

#include "networkV3.h"


void send_404(struct client_info *client) {
const char *c404 = "HTTP/1.1 404 Not Found\r\n"
			"Connection: close\r\n"
			"Content-Length: 9\r\n\r\nNot Found";

printf ("sending 404\n");
send(client->socket, c404, strlen(c404), 0);
drop_client(client);
}

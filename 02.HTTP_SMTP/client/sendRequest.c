#include "networkV2-1.h"


void send_request(SOCKET s, char *hostname, char *port, char *path) {

	char buffer[2048];

	sprintf (buffer, "GET /%s HTTP/1.1\r\n", path);
	sprintf (buffer + strlen(buffer), "Host: %s:%s\r\n", hostname, port);
	sprintf (buffer + strlen(buffer), "Connection: close\r\n");
	sprintf (buffer + strlen(buffer), "User-Agent: Hello There 1.0\r\n");
	sprintf (buffer + strlen(buffer), "\r\n");

	send (s, buffer, strlen(buffer), 0);
	printf ("Sent Headers: \n%s", buffer);
}

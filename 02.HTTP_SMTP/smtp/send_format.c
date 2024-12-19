#include "smtp.h"


//send formatted text to server
void send_format (const char *text, ...) {

	char buffer[1024];
	va_list args;
	va_start (args, text);
	vsprintf (buffer, text, args);
	va_end (args);

	send(address._socket, buffer, strlen(buffer), 0);

	printf ("Client: %s", buffer);
}

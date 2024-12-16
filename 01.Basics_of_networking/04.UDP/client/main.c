#include "networkV2-1.h"


void createSocket();
void closeSocket();
sock address;

int main (void) {

	createSocket();

	char *text = "Salam\n";
	int sent = sendto (address._socket, text, sizeof(text), 0, address.addr->ai_addr, address.addr->ai_addrlen);
	printf("Sent: %s\n\t%d bytes\n", text, sent);
	closeSocket();
	return 0;
}

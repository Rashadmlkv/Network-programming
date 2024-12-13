#include "networkV2-1.h"

const unsigned char *print_name(const unsigned char *msg,
		const unsigned char *p, const unsigned char *end);
void print_dns_message(const char *message, int msg_length);
void createSocket();
void closeSocket();
sock address;

int main (int argc, char *argv[]) {

	if (argc < 3) {
	
		fprintf (stderr, "Usage:\n\tdns_query hostname type\n");
		printf ("Example:\n\tdns_query example.com aaaa\n");
		exit (0);
	}

	if (strlen(argv[1]) > 255) {
	
		fprintf (stderr, "Hostname too long\n");
		exit (1);
	}

	unsigned char type;
	//strcmp == 0
	if (!strcmp(argv[2], "a")) {
	
		type = 1;
	} else if (!strcmp(argv[2], "mx")) {
	
		type = 15;
	} else if (!strcmp(argv[2], "txt")) {
	
		type = 16;
	} else if (!strcmp(argv[2], "aaaa")) {
	
		type = 255;
	} else {
	
		fprintf (stderr, "Unknown type '%s'. Use a, aaaa, txt, mx, or any.", argv[2]);
		exit (1);
	}


	createSocket();
	char query[1024] = {0xAB, 0xCD, /* ID */
				0x01, 0x00, /* Set recursion */
				0x00, 0x01, /* QDCOUNT */
				0x00, 0x00, /* ANCOUNT */
				0x00, 0x00, /* NSCOUNT */
				0x00, 0x00 /* ARCOUNT */};

	char *p = query + 12;
	char *h = argv[1];

	while (*h) {
	
		char *len = p;
		p++;
		if (h != argv[1])
			++h;

		while (*h && *h != '.') *p++ = *h++;
		*len = p - len -1;
	}

	*p++ = 0;
	*p++ = 0x00; *p++ = type; //qtype
	*p++ = 0x00; *p++ = 0x01; //qclass
	
	const int query_size = p - query;
	int sent = sendto (address._socket, query, query_size, 0, address.addr->ai_addr, address.addr->ai_addrlen);
	printf ("Sent: %d bytes\n", sent);
	print_dns_message(query, query_size);

	char read[1024];
	int received = recvfrom(address._socket, read, 1024, 0,0,0);
	printf ("Received %d bytes.\n", received);
	printf("\n");
	closeSocket();
	return 0;
}

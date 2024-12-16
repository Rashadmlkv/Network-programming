#include "networkV2-1.h"

const unsigned char *print_name(const unsigned char *msg,
                const unsigned char *p, const unsigned char *end);
void print_dns_message(const char *message, int msg_length) {

	if (msg_length < 12) {
	
		fprintf (stderr, "Message is too short to be valid.\n");
		exit (1);
	}

	const unsigned char *msg = (const unsigned char *) message;
	const int qr = (msg[2] & 0x80) >> 7;
	const int opcode = (msg[2] & 0x78) >> 3;
	const int aa = (msg[2] & 0x04) >> 2;
	const int tc = (msg[2] & 0x02) >> 1;
	const int rd = (msg[2] & 0x01);
	const int qdcount = (msg[4] << 8) + msg[5];
	const int ancount = (msg[6] << 8) + msg[7];
	const int nscount = (msg[8] << 8) + msg[9];
	const int arcount = (msg[10] << 8) + msg[11];

	//raw dns message
	for (int i = 0; i < msg_length; ++i) {
	
		unsigned char r = msg[i];
		printf ("%02d:	%02X %03d '%c'\n", i, r, r, r);
	}


	//print header section
	printf ("===============================================\n");
	printf ("==HEADER==\n");
	printf ("ID = %0x %0x\n", msg[0], msg[1]);
	printf ("QR = %d %s\n", qr, qr ? "response" : "query");
	printf ("OPCODE = %d ", opcode);
	switch (opcode) {
	
		case 0: printf ("standart\n"); break;
		case 1: printf ("reverse\n"); break;
		case 2: printf ("status\n"); break;
		default: printf ("?\n"); break;
	}
	printf ("AA = %d %s\n", aa, aa ? "authorative" : "");
	printf ("TC = %d %s\n", tc, tc ? "message trucated" : "" );
	printf ("RD = %d %s\n", rd, rd ? "recursion desired" : "");
	if (qr) {
	
		const int rcode = msg[3] & 0x07;
		printf ("RCODE = %d ", rcode);
		switch (rcode) {
		
			case 0: printf ("success\n"); break;
			case 1: printf ("format error\n"); break;
			case 2: printf ("server failure\n"); break;
			case 3: printf ("name error\n"); break;
			case 4: printf ("not implemented\n"); break;
			case 5: printf ("refused\n"); break;
			default: printf ("?\n"); break;
		}
		if (rcode != 0) return;
	}
	printf ("QDCOUNT = %d\n", qdcount);
	printf ("ANCOUNT = %d\n", ancount);
	printf ("NSCOUNT = %d\n", nscount);
	printf ("ARCOUNT = %d\n", arcount);


	//print question section
	printf ("==QUESTION==\n");	
	const unsigned char *p = msg + 12;
        const unsigned char *end = msg + msg_length;

	if (qdcount) {
	
		for (int i = 0; i < qdcount; ++i) {
		
			if (p >= end) {
			
				fprintf (stderr, "End of message.\n");
				exit (1);
			}

			printf ("Query %2d\n", i + 1);
			printf (" name ");

			p = print_name (msg, p, end);
			printf ("\n");

			if (p + 4 > end) {
			
				fprintf (stderr, "End of message.\n");
				exit (1);
			}

			const int type = (p[0] << 8) + p[1];
			printf (" type: %d\n", type);
			p += 2;

			const int qclass = (p[0] << 8) + p[1];
			printf (" class: %d\n", qclass);
			p += 2;
		}
	}


	//print answer section
	printf ("==ANSWER==\n");
	if (ancount || nscount || arcount) {

		for (int i = 0; i < ancount + nscount + arcount; ++i) {
		
			if (p >= end ) {
			
				fprintf (stderr, "End of message.\n");
				exit (1);
			}

			printf ("Answer %2d\n", i + 1);
			printf (" name: ");

			p = print_name(msg, p, end); 
			printf ("\n");

			if (p + 10 > end) {
			
				fprintf (stderr, "End of message.\n");
				exit (1);
			}

			const int type = (p[0] << 8) + p[1];
			printf (" type: %d\n", type);
			p += 2;

			const int qclass = (p[0] << 8) + p[1];
			printf (" class: %d\n", qclass);
			p += 2;

			const unsigned int ttl = (p[0] << 24) + (p[1] << 16) + (p[2] << 8) + p[3];
			printf (" ttl: %u\n", ttl);
			p += 4;

			const int rdlen = (p[0] << 8) + p[1];
			printf (" rdlen: %d\n", rdlen);

			if (p + rdlen > end) {
			
				fprintf (stderr, "End of message.\n");
				exit (1);
			}

			if (rdlen == 4 && type == 1) {

				//a rec
				printf ("Address ");
				printf ("%d.%d.%d.%d\n", p[0],p[1],p[2],p[3]);
			} else if (type == 15 && rdlen > 3) {
			
				//mx rec
				const int preference = (p[0] << 8) + p[1];
				printf (" pref: %d\n", preference);
				printf ("MX: ");
				print_name (msg, p+2, end);
				printf ("\n");
			} else if (rdlen == 16 && type == 28) {
			
				//aaaa rec
				printf ("Address ");
				for (int j = 0; j < rdlen; j += 2) {
				
					printf ("%02x%02x", p[j], p[j + 1]);
					if (j + 2 < rdlen) printf (":");
				}
				printf ("\n");
			} else if (type == 16) {
			
				//txt rec
				printf ("TXT '%.*s'\n", rdlen - 1, p + 1);
			} else if (type == 5) {
			
				//cname rec
				printf ("CNAME: ");
				print_name (msg, p , end);
				printf ("\n");
			}
			p += rdlen;
		}
	}

	if (p != end) {
	
		printf ("There is some unread data left over.\n");
	}

	printf ("\n");
}

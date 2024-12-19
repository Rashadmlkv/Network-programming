#include "smtp.h"


//get response from server and send to parsing for code
void wait_on_response (int expecting) {

	char response[MAXRESPONSE + 1];
	char *p = response;
	char *end = response + MAXRESPONSE;
	int code = 0;

	do {
	
		int received = recv (address._socket, p, end - p, 0);

		if (received < 1) {
		
			fprintf (stderr, "Connection dropped\n");
			exit (1);
		}

		p += received;
		*p = 0;

		if (p == end) {
		
			fprintf (stderr, "Server response too large\n");
			fprintf (stderr, "%s", response);
			exit (1);
		}

		code = parse_response (response);
	} while (code == 0);

	if (code != expecting) {
	
		fprintf (stderr, "Error from server\n");
		fprintf (stderr, "%s", response);
		exit (1);
	}

	printf ("Server: %s", response);
}

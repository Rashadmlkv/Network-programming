#include "networkV2-1.h"


void parse_url (char *url, char **hostname, char **port, char **path) {

	printf ("URL: %s\n", url);

	char *p = strstr (url, "://");
	

	//parse protocol
	char *protocol = 0;

	if (p) {
	
		protocol = url;
		*p = 0;
		p += 3;
	} else {
	
		p = url;
	}

	if (protocol) {
	
		if (strcmp (protocol, "http")) {

			fprintf (stderr,
				       	"Unknown protocol '%s'. Only 'http' is supported.\n", protocol);
			exit (1);
		}
	}


	//parse hostname
	*hostname = p;

	while (*p && *p != ':' && *p != '/' && *p != '#') ++p;


	//parse port
	*port = "80";

	if (*p == ':') {
	
		*p++ = 0;
		*port = p;
	}

	while (*p && *p != '/' && *p != '#') ++p;


	//parse path
	*path = p;

	if (*p == '/') {
	
		*path = p+1;
	}

	*p = 0;


	//parse hash
	while (*p && *p != '#') ++p;
	
	if (*p == '#') {
	
		*p = 0;
	}

	//print parsed
	printf ("hostname: %s\n", *hostname);
	printf ("port: %s\n", *port);
	printf ("path: %s\n", *path);
}

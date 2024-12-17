#include "networkV3.h"

#define BSIZE 1024

void serve_resource(struct client_info *client, const char *path) {

	printf("serve_resource %s %s\n", get_client_address(client), path);

	if (strcmp (path, "/") == 0) {
	
		path = "/index.html";
	}

	if (strlen(path) > 100) {
	
		send_400(client);
		return;
	}

	if (strstr (path, "..")) {
	
		send_404(client);
		return;
	}

	char full_path[128];
	sprintf(full_path, "public%s", path);
    printf ("%s\n", full_path);
	#ifdef _WIN32
		char *p = full_path;

		while (*p) {
		
			if (*p == '/')
			{
				*p = '\\';
			}
			++p;
		}
	#endif

	FILE *fp = fopen (full_path, "rb");

	if (!fp) {
	
		fprintf (stderr, "fopen() failed.\n");
		send_404(client);
		return;
	}

	fseek (fp, 0L, SEEK_END);
	size_t cl = ftell(fp);
	rewind (fp);

	const char *ct = get_content_type(full_path);
	char buffer[BSIZE];

	sprintf(buffer, "HTTP/1.1 200 OK\r\n");
	send(client->socket, buffer, strlen(buffer), 0);
	sprintf(buffer, "Connection: close\r\n");
	send(client->socket, buffer, strlen(buffer), 0);
	sprintf(buffer, "Content-Length: %lu\r\n", cl);
	send(client->socket, buffer, strlen(buffer), 0);
	sprintf(buffer, "Content-Type: %s\r\n", ct);
	send(client->socket, buffer, strlen(buffer), 0);
	sprintf(buffer, "\r\n");
	send(client->socket, buffer, strlen(buffer), 0);

	int r = fread (buffer, 1 , BSIZE, fp);
	while (r) {
	
		send (client->socket, buffer, r, 0);
		r = fread (buffer, 1, BSIZE, fp);
	}

	fclose (fp);
	drop_client (client);
}

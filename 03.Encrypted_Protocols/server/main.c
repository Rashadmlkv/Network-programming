#include "secnetwork.h"


void createSocket ();
void closeSocket (SSL_CTX ctx);
sock address;
int main (void) {

	//initialize SSL library
	SSL_library_init ();
	OpenSSL_add_all_algorithms ();
	SSL_load_error_strings ();

	//create SSL context
	SSL_CTX *ctx = SSL_CTX_new (TLS_server_method ());
	if (!ctx) {
	
		fprintf (stderr, "SSL_CTX_new() failed\n");
		return 1;
	}

	//assign certificates
	if (!SSL_CTX_use_certificate_file (ctx, "cert.pem", SSL_FILETYPE_PEM)
			|| !SSL_CTX_use_PrivateKey_file (ctx, "key.pem", SSL_FILETYPE_PEM)) {
	
		fprintf (stderr, "SSL_CTX_use_certificate_file() failed\n");
		return 1;
	}

	createSocket ();

	while (1) {
	
		//accept new connection
		printf ("Waiting for new connection\n");
		struct sockaddr_storage client;
		socklen_t clientLen = sizeof (client);
		SOCKET clientSocket = accept (address._socket,
						(struct sockaddr*) &client, &clientLen);
		if (!ISVALIDSOCKET (clientSocket)) {
		
			fprintf (stderr, "accept() failed\n");
			return 1;
		}
		char addrbuff[100];
		getnameinfo ((struct sockaddr*) &client,
				clientLen,
			       	addrbuff,
			       	sizeof (addrbuff),
			       	0,0,
			       	NI_NUMERICHOST);
		printf ("Client %s connected\n", addrbuff);
	
		//ssl on tcp
		SSL* ssl = SSL_new (ctx);
		if (!ctx) {
		
			fprintf (stderr, "SSL_new() failed\n");
			return 1;
		}
		
		//accept ssl connection
		SSL_set_fd (ssl, clientSocket);
		if (SSL_accept (ssl) <= 0) {
		
			fprintf (stderr, "SSL_accept() failed\n");
			ERR_print_errors_fp (stderr);

			SSL_shutdown(ssl);
			CLOSESOCKET(clientSocket);
			SSL_free(ssl);
			continue;
		}
		printf ("SSL connection using %s\n", SSL_get_cipher (ssl));
		
		//read request
		char request[1024];
		int received = SSL_read (ssl, request, 1024);
		printf ("received %d bytes\n", received);

		//send response
		const char* response = 
			"HTTP/1.1 200 OK\r\n"
			"Connection: close\r\n"
			"Content-Type: text/plain\r\n\r\n"
			"Local time is: ";
		int sent = SSL_write (ssl, response, strlen (response));
		printf ("sent %d of %d bytes\n", sent, (int) strlen (response));

		//send time
		time_t timer;
		time (&timer);
		char* timer_msg = ctime (&timer);
		sent = SSL_write (ssl, timer_msg, strlen (timer_msg));
		printf ("Sent %d of %d bytes\n", sent, (int) strlen (timer_msg));

		//close connection
		SSL_shutdown (ssl);
		CLOSESOCKET (clientSocket);
		SSL_free (ssl);
	}
	CLOSESOCKET(address._socket);
	SSL_CTX_free(ctx);
	return 0;
}

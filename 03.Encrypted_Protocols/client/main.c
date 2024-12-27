//This client can connect to a given HTTPS web server and
// request the root document /.


#include "secnetwork.h"

void createSocket (char* hostname, char* port);
sock address;


int main (int argc, char *argv[]) {

	//SSL init
	SSL_library_init();
	OpenSSL_add_all_algorithms();
	SSL_load_error_strings();

	//SSL context
	SSL_CTX *ctx = SSL_CTX_new(TLS_client_method());
	if (!ctx) {
	
		fprintf (stderr, "SSL_CTX_new() failed\n");
		return 1;
	}

	//check arguments
	if (argc != 3) {

                fprintf (stderr, "Usage: <hostname> <port>\n");
                return 1;
        }

	//create tcp connection
	createSocket(argv[1], argv[2]);

	//create tls on tcp
	SSL *ssl = SSL_new(ctx);
	if (!ctx) {

		fprintf (stderr, "SSL_new() failed\n");
		CLOSESOCKET (address._socket);
		return 1;
	}

	if (!SSL_set_tlsext_host_name(ssl, argv[1])) {
	
		fprintf (stderr, "SSL_set_tlsext_host_name() failed\n");
		ERR_print_errors_fp (stderr);
		CLOSESOCKET (address._socket);
		return 1;
	}

	SSL_set_fd(ssl, address._socket);
	if (SSL_connect (ssl) == -1) {
	
		fprintf (stderr, "SSL_connect() failed\n");
		ERR_print_errors_fp (stderr);
		CLOSESOCKET (address._socket);
		return 1;
	}

	//print cipher and certificate
	printf ("SSL/TLS using %s\n", SSL_get_cipher(ssl));
	X509 *cert = SSL_get_peer_certificate(ssl);
	if (!cert) {
	
		fprintf (stderr , "SSL_get_peer_certificate() failed\n");
		CLOSESOCKET (address._socket);
		return 1;
	}

	char* tmp;
	if ((tmp = X509_NAME_oneline (X509_get_subject_name (cert), 0, 0))) {
	
		printf ("subject: %s\n", tmp);
		OPENSSL_free(tmp);
	}

	if ((tmp = X509_NAME_oneline (X509_get_issuer_name (cert), 0, 0))) {
	
		printf ("issuer: %s\n", tmp);
		OPENSSL_free (tmp);
	}

	X509_free (cert);


	//send http request
	char buffer[2048];

	sprintf(buffer, "GET / HTTP/1.1\r\n");
	sprintf(buffer + strlen(buffer), "Host: %s:%s\r\n", argv[1], argv[2]);
	sprintf(buffer + strlen(buffer), "Connection: close\r\n");
	sprintf(buffer + strlen(buffer), "User-Agent: https_simple\r\n");
	sprintf(buffer + strlen(buffer), "\r\n");

	SSL_write (ssl, buffer, sizeof (buffer));
	printf ("Sent headers: \n\n%s", buffer);


	//wait for response
	while (1) {
	
		int received = SSL_read (ssl, buffer, sizeof (buffer));

		if (received < 1) {
		
			printf ("Connection closed by peer\n");
			break;
		}

		printf ("Received (%d bytes): '%.*s'\n",
		      		received, received, buffer );
	}

	return 0;
}

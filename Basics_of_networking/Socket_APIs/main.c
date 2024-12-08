#include "network.h"

int main()
{
	//in windows socket has to be initialize first
	#if defined (_WIN32) || (WIN32) || (_WIN32_)
		WSDATA d;

		if ( WSAStartup( MAKEWORD( 2 , 2 ), &d ) ) {
	
			fprintf(stderr, "Failed to initialize socket.\n");
			return -1;
		}

	#endif

	printf("Socket API ready to use.\n");
	struct addrinfo hints;
	printf("Configuring local address..\n");
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET; //IPv4
	hints.ai_socktype = SOCK_STREAM; //TCP
	hints.ai_flags = AI_PASSIVE;

	struct addrinfo *bind_address;
	getaddrinfo(0, "8080", &hints, &bind_address);

	printf("Creating socket...\n");
	SOCKET socketListen;
	socketListen = socket(bind_address->ai_family, bind_address->ai_socktype, bind_address->ai_protocol);

	if ( !ISVALIDSOCKET(socketListen) ) {
	
		fprintf(stderr, "Socket creation failed (%d)\n", GETSOCKETERRNO());
		return -1;
	}

	printf("Binding socket to local address\n");
	if (bind(socketListen, bind_address->ai_addr, bind_address->ai_addrlen)) {
	
		fprintf(stderr, "Failed to bind %d. \n", GETSOCKETERRNO());
		return -1;
	}
	freeaddrinfo(bind_address);

	//listen up to 10 connections
	if (listen(socketListen, 10) < 0 ) {
	
		fprintf(stderr, "Listening failed %d.\n", GETSOCKETERRNO());
	} else {
	
		printf("Listening for connection..\n");
	}

	printf("Waiting for connections");
	struct sockaddr_storage clientAddress;
	socklen_t client_len = sizeof(clientAddress);
	SOCKET socketClient = accept(socketListen, (struct sockaddr*) &clientAddress, &client_len);

	if (!ISVALIDSOCKET(socketClient)) {
	
		fprintf(stderr, "Couldn't new create socket for connection %d.\n", GETSOCKETERRNO());
		return -1;
	}	

	printf("Client connected.\n");
	char address_buffer[100];
	getnameinfo((struct sockaddr*)&clientAddress, client_len, address_buffer, sizeof(address_buffer), 0,0, NI_NUMERICHOST);
	printf("%s\n", address_buffer);

	printf("reading request..\n");
	char request[1024];
	int bytes_received = recv(socketClient, request, 1024, 0); //read
	printf("READ %d BYTES\n", bytes_received);
	printf("%.*s", bytes_received, request);


	printf("Sending response..\n");
	time_t datetime;
        time(&datetime);
	const char *response = 
		"HTTP/1.1 200 OK\r\n"
		"Connection: close\r\n"
		"Content-Type: text/plain\r\n\r\n"
		"Local time is: ";
	char *time_msg = ctime(&datetime);
	int bytes_sent = send(socketClient, response, strlen(response), 0);
	bytes_sent = send(socketClient, time_msg, strlen(time_msg), 0);
	printf("Sent %d of %d bytes.\n", bytes_sent, (int)strlen(response));
	printf("Sent %d of %d bytes.\n", bytes_sent, (int)strlen(time_msg));



	printf("closing connection..\n");
	CLOSESOCKET(socketClient);
	CLOSESOCKET(socketListen);

	#if defined (_WIN32) || (WIN32) || (_WIN32_)
		WSACleanup();
	#endif

	return 0;
}

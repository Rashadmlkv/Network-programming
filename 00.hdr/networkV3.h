#ifndef NETWORK_H
#define NETWORK_H



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define MAX_REQUEST_SIZE 2047

//WINDOWS
#if defined (_WIN32) && !(UNIX)
#ifndef (WIN32_WINNT)
#define (WIN32_WINNT) 0x0A00 
#endif //WIN32_WINNT
#include <winsock2.h>
#include <ws2cpip.h>
#include <conio.h>
#pragma comment(lib, "ws2_32.lib")

//UNIX
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>
#endif //WIN32


#if defined (_WIN32) && !(UNIX)
#define ISVALIDSOCKET(s) ( s != INVALID_SOCKET )
#define CLOSESOCKET(s) ( closesocket(s) )
#define GETSOCKETERRNO() ( WSAGetLastError() )

#else
#define ISVALIDSOCKET(s) ( (s) >= 0 )
#define CLOSESOCKET(s) ( close(s) )
#define GETSOCKETERRNO() ( errno )
#define SOCKET int
#endif


struct Sock {

	struct addrinfo *addr;
	SOCKET _socket;
};
typedef struct Sock sock;
extern sock addresss;

struct client_info *get_client(SOCKET s);
void create_socket(const char* host, const char *port);
void drop_client(struct client_info *client);
const char *get_client_address(struct client_info *ci);
const char *get_content_type(const char* path);
void send_400(struct client_info *client);
void send_404(struct client_info *client);
void serve_resource(struct client_info *client, const char *path);
fd_set wait_on_clients();

struct client_info {

	struct sockaddr_storage address;
	struct client_info *next;
	char request[MAX_REQUEST_SIZE + 1];
	socklen_t address_length;
	SOCKET socket;
	int received;
};
extern struct client_info *clients;

#endif //NETWORK_H


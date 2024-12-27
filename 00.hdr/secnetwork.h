#ifndef NETWORK_H
#define NETWORK_H



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <openssl/crypto.h>
#include <openssl/x509.h>
#include <openssl/pem.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

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
extern sock address;
#endif //NETWORK_H

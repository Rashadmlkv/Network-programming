#ifndef NETWORK_H
#define NETWORK_H



#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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



#endif //NETWORK_H


int getAddress( int argc , char *argv[] , struct addrinfo **address);
int createSocket( struct addrinfo **address , SOCKET *socketpeer );
int connectAddress( struct addrinfo **address , SOCKET *socketpeer );
void programLoop( SOCKET *socketpeer);
void closeSocket( SOCKET *socketpeer);

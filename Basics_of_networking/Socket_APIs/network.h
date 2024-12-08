#ifndef NETWORK_H
#define NETWORK_H

#include <stdio.h>
#include <time.h>
#include <string.h>

//Windows 32 bit system
//defined  supports multi parameters
#if defined (_WIN32) || (WIN32) || (_WIN32_) && !(UNIX)
#ifndef (_WIN32_WINNT)
#define (_WIN32_WINNT) 0x0A00
#endif //_WIN32_WINNT
#include <winsock2.h>
#include <ws2tcpip.h>
#define ISVALIDSOCKET(s) ( s != INVALID_SOCKET )
#define CLOSESOCKET(s) (closesocket(s))
#define GETSOCKETERRNO() (WSAGetLastError())
#pragma comment (lib, "ws2_32.lib")

//Unix systems (Linux, macOS)
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <netdb.h>
#define SOCKET int
#define ISVALIDSOCKET(s) ( (s) >= 0 )
#define CLOSESOCKET(s) (close(s))
#define GETSOCKETERRNO() (errno)
#endif //_WIN32

#endif //NETWORK_H

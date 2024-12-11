#ifndef NETWORK_H
#define NETWORK_H

#include <stdio.h>
#include <stdlib.h>

#if defined(_WIN32)  //In windows systems this will compile
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0A00
#endif
#include <winsock2.h>
#include <iphlpapi.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")


#else		//In linux/macOS systems this will compile
#include <sys/socket.h>
#include <netdb.h>
#include <ifaddrs.h>
#include <stdlib.h>
#endif

#endif //NETWORK_H

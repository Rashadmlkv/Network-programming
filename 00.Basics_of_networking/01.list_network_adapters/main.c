#include "network.h"

int main()
{
	//windows
	/*
		WSADATA d;
		
		if ( WSAStartup( MAKEWORD( 2 , 2 ) , &d ) ) {
			
			printf("Failed to initialize.\n");
			return -1;
		}

		DWORD asize = 20000;
		PIP_ADAPTER_ADDRESSES adapters;

		do {
		
			adapters = (PIP_ADAPTER_ADDRESSES)malloc(asize);

			if (!adapters) {
			
				printf("Coultdn't allocate %ld size\n", asize);
				WSACleanup();
				return -1;
			}

			int r = GetAdapterAdresses(AF_UNSPEC, GAA_FLAG_INCLUDE_PREFIX, 0, adapters, &asize);

			if ( r == ERROR_BUFFER_OVERFLOW ) {
			
				printf("GetAdaptersAddresses wants %ld bytes.\n", asize);
				free(adapters);
			
			} else if ( r == ERROR_SUCCESS ) {
			
				break;
			
			} else {
			
				printf("Error from GetAdaptersAddresses: %d\n", r);
				free(adapters);
				WSACleanup();
				return -1;
			}
		} while (!adapters);


		while ( adapters ) {
		
			printf("\nNetwork adapter name: %S\n", adapter->FriendlyName);

			PIP_ADAPTER_UNICAST_ADDRESS address = adapters->FirstUnicastAddress;
			while ( address ) {

				printf("\t%s", address->Address.lpSockaddr->sa_family == AFINET ? "IPv4" : "IPv6");

				char ap[100];

				getnameinfof(address->Address.lpSockaddrLength, ap, sizeof(ap), 0,0, NI_NUMERICHOST);
				printf("\t%s\n", ap);
				address = address->Next;
			}
			adapters = adapters->Next;
		}
		WSACleanup();
		printf("Cleaned socket\n");
		return 0;
*/ 


	//linux
	
	struct ifaddrs *adresses;

	if (getifaddrs(&adresses)==-1)
		return -1;

	while(adresses)
	{
		int family = adresses->ifa_addr->sa_family;
		if (family == AF_INET || family == AF_INET6)
		{
			printf("Netowrk adapter name: %s\n", adresses->ifa_name);
			printf("\tIP version: %s", family == AF_INET ? "IPv4" : "IPv6");

			char ap[100];
			const int family_size = family == AF_INET ?
			sizeof(struct sockaddr_in) : sizeof(struct sockaddr_in6);

			getnameinfo(adresses->ifa_addr, family_size, ap, sizeof(ap), 0,0, NI_NUMERICHOST);
			printf("\t%s\n\n", ap);
		}
		adresses = adresses->ifa_next;
	}
}

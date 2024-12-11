#include "network.h"

int mainLoop(SOCKET *sock)
{

	fd_set master;
	FD_ZERO(&master);
	FD_SET(*sock, &master);
	SOCKET max = *sock, iter;

	while (1)
	{
		fd_set reads;
		reads = master;

		if (select(max + 1, &reads, 0, 0, 0) < 0)
		{

			fprintf(stderr, "select() failed.\n");
			return 1;
		}

		for (iter = 1; iter <= max; iter++)
		{

			if (FD_ISSET(iter, &reads))
			{

				// accept
				if (iter == *sock)
				{

					struct sockaddr_storage clientAddr;
					socklen_t clientLen = sizeof(clientAddr);
					SOCKET sockClient = accept(*sock, (struct sockaddr *)&clientAddr, &clientLen);

					if (!ISVALIDSOCKET(sockClient))
					{

						fprintf(stderr, "Accept failed\n");
						return 1;
					}

					FD_SET(sockClient, &master);
					if (sockClient > max)
						max = sockClient;

					char addr[100];
					getnameinfo((struct sockaddr *)&clientAddr, clientLen, addr, sizeof(addr), 0, 0, NI_NUMERICHOST);
					printf("New connection from %s\n", addr);
				}
				// read
				else
				{

					char read[1024];
					int received = recv(iter, read, 1024, 0);
					if (received < 1)
					{

						FD_CLR(iter, &master);
						CLOSESOCKET(iter);
						continue;
					}
					SOCKET j;
for (j = 1; j <= max; ++j) {
if (FD_ISSET(j, &master)) {
if (j == *sock || j == iter)
continue;
else
send(j, read, received, 0);
}
}
				}
			}
		}

	}
	return 0;
}

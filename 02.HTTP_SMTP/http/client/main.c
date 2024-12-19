#include "networkV2-1.h"

#define TIMEOUT 5.0
#define RESPONSE_SIZE 8192

void parse_url(char *url, char **hostname, char **port, char **path);
void send_request(SOCKET s, char *hostname, char *port, char *path);
void connect_to_host(char *hostname, char *port);
void closeSocket();
sock address;

int main(int argc, char *argv[])
{

	if (argc != 2)
	{

		fprintf(stderr, "Usage: url\n");
		return 1;
	}

	// argument to url
	char *url = argv[1];
	char *hostname, *port, *path;

	// check url and connect to server
	parse_url(url, &hostname, &port, &path);
	connect_to_host(hostname, port);
	send_request(address._socket, hostname, port, path);

	// Server response data
	const clock_t start_time = clock();
	char response[RESPONSE_SIZE + 1];
	char *p = response, *q;
	char *end = response + RESPONSE_SIZE;
	char *body = 0;

	enum
	{
		length,
		chunked,
		connection
	};
	int encoding = 0;
	int remaining = 0;

	// get response
	while (1)
	{

		// check timeout
		if ((clock() - start_time) / CLOCKS_PER_SEC > TIMEOUT)
		{

			fprintf(stderr, "timeout after %.2f seconds\n", TIMEOUT);
			return 1;
		}

		if (p == end)
		{

			fprintf(stderr, "out of buffer space\n");
			return 1;
		}

		// set non blocking communication via select
		fd_set reads;
		FD_ZERO(&reads);
		FD_SET(address._socket, &reads);

		struct timeval timeout;
		timeout.tv_sec = 0;
		timeout.tv_usec = 200000;

		if (select(address._socket + 1, &reads, 0, 0, &timeout) < 0)
		{

			fprintf(stderr, "select() failed. (%d)\n", GETSOCKETERRNO());
			return 1;
		}

		// recieve data
		if (FD_ISSET(address._socket, &reads))
		{

			int received = recv(address._socket, p, end - p, 0);

			if (received < 1)
			{

				if (encoding == connection && body)
				{

					printf("%.*s", (int)(end - body), body);
				}
				printf("\nConnection closed by peer.\n");
				break;
			}

			p += received;
			*p = 0;

			if (!body && (body == strstr(response, "\r\n\r\n")))
			{

				*body = 0;
				body += 4;
			}

			printf("Received Headers:\n%s\n", response);

			q = strstr(response, "\nContent-Length: ");

			if (q)
			{

				encoding = length;
				q = strchr(q, ' ');
				q += 1;
				remaining = strtol(q, 0, 10);
			}
			else
			{

				q = strstr(response, "\nTransfer-Encoding: chunked");
				if (q)
				{

					encoding = chunked;
					remaining = 0;
				}
				else
				{

					encoding = connection;
				}
			}

			printf("\nReceived Body:\n");

			if (body)
			{

				if (encoding == length)
				{

					if (p - body >= remaining)
					{

						printf("%.*s", remaining, body);
						break;
					}
				}
				else if (encoding == chunked)
				{

					do
					{

						if (remaining == 0)
						{

							if ((q = strstr(body, "\r\n")))
							{

								remaining = strtol(body, 0, 16);
								if (!remaining)
									goto finish;
								body = q + 2;
							}
							else
							{
								break;
							}
						}

						if (remaining && p - body >= remaining)
						{

							printf("%.*s", remaining, body);
							body += remaining + 2;
							remaining = 0;
						}
					} while (!remaining);
				} // else if (encoding)
			} // if (body)
		} // if fd_isset
	} // while
finish:
	closeSocket();
	return 0;
}

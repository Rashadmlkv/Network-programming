#include "smtp.h"


sock address;


int main (void) {

	char hostname[MAXINPUT];
	get_input ("mail server: ", hostname);

	printf ("Connecting to host: %s:25\n", hostname);
	connect_to_host (hostname, "25");


	//handshake
	wait_on_response (220);
	send_format ("HELO RASHAD\r\n");
	wait_on_response (250);


	//sender & receiver
	char sender[MAXINPUT];
	get_input ("from: ", sender);
	send_format ("MAIL FROM:<%s>\r\n", sender);
	wait_on_response (250);
	
	char recipient[MAXINPUT];
	get_input ("to: ", recipient);
	send_format ("RCPT TO:<%s>\r\n", recipient);
	wait_on_response (250);

	
	//DATA
	send_format ("DATA\r\n");
	wait_on_response (354);

	char subject[MAXINPUT];
	get_input ("subject: ", subject);

	send_format ("FROM:<%s>\r\n", sender);
	send_format ("TO:<%s>\r\n", recipient);
	send_format ("Subject:%s\r\n", subject);

	time_t timer;
	time (&timer);

	struct tm* timeinfo;
	timeinfo = gmtime (&timer);

	char date[128];
	strftime (date, 128, "%a, %d %b %Y %H:%S +0000", timeinfo);
	send_format ("Date:%s\r\n", date);

	send_format ("\r\n");


	//BODY
	while (1) {
	
		char body[MAXINPUT];
		get_input ("> ", body);
		send_format ("%s\r\n", body);
		if (strcmp (body, ".") == 0) {
		
			printf ("Noqte\n");
			break;
		}
	}

	printf ("Cixis\n");
	wait_on_response (250);

	send_format ("QUIT\r\n");
	wait_on_response (221);

	printf ("\nClosing socket\n");
	CLOSESOCKET (address._socket);
#ifdef _WIN32
	WSACleanup();
#endif

	printf ("Closed\n");
	return 0;
}

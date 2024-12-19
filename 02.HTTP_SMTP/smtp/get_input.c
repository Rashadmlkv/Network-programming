#include "smtp.h"


//promt user for input
void get_input (const char *prompt, char *buffer) {

	printf ("%s", prompt);

	buffer[0] = 0;
	fgets (buffer, MAXINPUT, stdin);
	const int read = strlen (buffer);
	if (read > 0) {
	
		buffer [read - 1] = 0;
	}
}

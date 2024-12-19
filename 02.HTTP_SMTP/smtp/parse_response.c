#include "smtp.h"


//parse digit part of response
//return response code in success
//return 0 in failure
int parse_response (const char *response) {

	const char *k = response;

	if (!k[0] || !k[1] || !k[2]) return 0;


	for (; k[3]; ++k) {
	
		if (k == response || k[-1] == '\n') {
		
			if (isdigit( k[0]) && isdigit( k[1]) && isdigit( k[2])) {
			
				if (k[3] != '-') {
				
					if (strstr (k, "\r\n")) {
					
						return strtol (k, 0, 10);
					}
				}
			}
		}
	}
	return 0;
}

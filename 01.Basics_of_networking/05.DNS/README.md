LEARNED:
1. DNS links hostname to IP and IP to hostname. DNS services stores frequenly visited sites in cache, as PC do.
OS looks cache first for address if not found goes to DNS service and if not found in there then DNS service goes to another service.
2. Has 5 types - A, AAAA, Mx, TXT, CNAME, *ALL/ANY
A and AAAA links name to IP. One for ip4 , another ip6.
MX mail server information
TXT information about domain.
CNAME makes alias of domain like mm.com to www.mm.com
DNS server port 53 packet UDP.
TCP fallback or DNS transport over TCP is sending pack over tcp when answer size is big

getaddrinfo() sends DNS query. returns linked list of addresses specified in hints into addrinfo struct. 
AI_NUMERICHOST flag is use when you know ip and restrict dns lookup for name. same to numericserv.



LOOKUP:
https://stackoverflow.com/questions/13514614/why-is-network-byte-order-defined-to-be-big-endian
https://www.rfc-editor.org/ien/ien137.txt

CHANGED:
    nothing but copied createSocket and closeSocket functions from UDP file. First time applied reusabilty.
